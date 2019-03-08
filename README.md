# Configure + Build
+ qibuild configure -c "toolchain name"
+ qibuild make -c "toolchain name"
# Set up Game Controller & Tester
+ move to ~/GameController2018/
+ java -jar GameController.jar
+ java -jar GameControllerTester.jar
# Structure:
Game controller files are conducted with gameControllData headers. 
Udp class uses the same data type to transfer information
# Port Numbers
+ File with port numbers:  
/GameController2018/include/RoboCupGameControlData.h
+ GC data transfering:  
Using broadcast address /192.168.1.255  
Listening on address /192.168.1.68  
# Achievements
+ Transfering messages from GC to GCTester using udp protocol and Linux Socket
+ adding some API to deliver messages with udp (25.02)
# Current ideas about GC
+ Run Game Controller
+ Analyse GameControlData class
+ Analyse GameController messages
# Current ideas about Transfering data
+ Easy way  
Read [InTeReStInG](https://github.com/UNSWComputing/rUNSWift-2018-release/tree/master/robot/gamecontroller) code.  
Find START message handler.  
Write module the same way.  
+ Cool way  
Use AL:: library and Brocker API to handler the START message.  
We can write separate class in which we'll use brockers to call methods from other modules
+ Current way  
We have to write special class, which will contain data and team info
# Test abilities
WiFi local network
+ Only computers  
On first PC GameController is executed. This PS is a message sender. Messages contains information about commands, game style, timeout etc. The second computer reads GCData from UDP port and parses data in readable way.
We can provide a reliable connection and data transfering. After that we can start the next step  
+ Comming soon ...

# address finding out  
My PC 

  wlp3s0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
  inet 192.168.1.68
