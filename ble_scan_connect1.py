
from bluepy.btle import Peripheral, UUID
from bluepy.btle import Scanner, DefaultDelegate
class ScanDelegate(DefaultDelegate):
	def __init__(self):
		DefaultDelegate.__init__(self)
	def handleDiscovery(self, dev, isNewDev, isNewData):
		if isNewDev:
			print ("Discovered device", dev.addr)
		elif isNewData:
			print ("Received new data from", dev.addr)
scanner = Scanner().withDelegate(ScanDelegate())
devices = scanner.scan(10.0)
n=0
for dev in devices:
	print( "%d: Device %s (%s), RSSI=%d dB" % (n, dev.addr,dev.addrType, dev.rssi))
	n += 1
	for (adtype, desc, value) in dev.getScanData():
		print (" %s = %s" % (desc, value))
number = input('Enter your device number: ')
print('Device', number)
print(devices[number].addr)
print ("Connecting...")
dev = Peripheral(devices[number].addr, 'random')
dev.setDelegate( ScanDelegate() )
print ("Services...")
for svc in dev.services:
	print (str(svc))
try:
	testService = dev.getServiceByUUID(UUID(0xa000))
	for ch in testService.getCharacteristics():
		print (ch)
	ch = dev.getCharacteristics(uuid=UUID(0xa001))[0]
	ch.write("write??")
	notify=ch.getHandle()+1
	dev.writeCharacteristic(notify,b"\x01\x00",withResponse=True)
	while True:
		if dev.waitForNotifications(1.0):
			print( "button pressed" )
			continue;
		else:
			print ( "waiting" )
finally:
	dev.disconnect()
