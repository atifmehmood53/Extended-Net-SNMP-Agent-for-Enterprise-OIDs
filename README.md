# Extended Net-SNMP Agent For Enterprise OIDs
This project was completed as a Job Hiring Task for **Afiniti Inc.**
## Task discription 
In this task we had to setup an SNMP agent along with custom enterprise OIDs on a Linux server to be monitored.
## Research Findings
Since I never worked with the SNMP protocol before I had to do some research on my own. I am not including the details of the protocol itself because it will make the readme lengthy. But we must discuss how Net-SNMP work because my solution extends it. Net-SNMP has a daemon called **snmpd** which is responsible to serve the requests for the objects it is exposing. These objects can theoretically anything but they are usually meaningful for the end manager. These objects are uniquely identified by their OIDs (**Object Identifiers**). These OIDs are registered in the agent itself but they are also defined in MIBs (**Management Information Base**). These are the files which define the structure of objects and their OIDs. These files are also useful for manager because it will be able to understand that which resources are available from a particulate agent. These MIBs can also be used to translate OIDs into more human readable form as well as generating the basic structure of the code to extend net-snmp using MIB modules and sub agent. The whole snmp agent is dependent on snmp.conf and snmpd.conf files and we can update these configurations to meet our needs. Now that we have some context of how net-snmp works we can extend it in many ways, here are some of them which I have explored in my solution: 
1. Using `extend` command. In **snmpd.conf** file we can define these commands which are very powerfull to run any arbitrary programme and return the result as well as the return status code. It also has a variant `extend-sh` which can be used to run any shell command. These command doesn't require any special information of snmp itself and return output in a specific format.
2. Using `pass` command. This is also defined **snmpd.conf** file. It is a more general mechanism for implementing arbitrary MIB objects. The specified command will be invoked for any request within the named MIB subtree, and passed details of the requested OID. It should return the information relevant to the requested OID.
3. Using sub agent, we can create our own sub agents. The benefit of this are numerous, such as it can be either connected to the master agent as a sub agent or can be run independently. This sub agent includes MIB modules to respond to custom OIDs.  We can  generate MIB modules' structure code in C to implement this using the following command:
``mib2c <MIB-NAME:objectName>``
Then we can edit generated files objectName.c and objectName.h to fit our needs. 
There are also some other ways which I could not explore due to time constraints. 
> **You must have to bulid net-snmp from source to get this mib2c feature enabled. But you don't need it just to run my solution.**

 http://net-snmp.sourceforge.net/wiki/index.php/FAQ:Agent_07
 http://net-snmp.sourceforge.net/wiki/index.php/TUT:Writing_a_Subagent
  
# Requirements

To run my solution on your machine, you should have the following requirements installed:
- Ubuntu 16.xx or 18.xx or 20.xx
- PostgreSQL 12 (https://www.postgresql.org/download/linux/ubuntu/) 

# Dependencies
- snmpd
- snmp 
- libsnmp-dev
- snmp-mibs-downloader
- libsnmp-dev 
- make 
- gcc 
- libpq-dev

run the following command to install them 

```sudo apt install snmpd snmp libsnmp-dev make gcc libpq-dev snmp-mibs-downloader```
# Setup PostgreSQL, Required User, Database and Table
you can follow the steps from PosgreSql's official guide to setup it. https://www.postgresql.org/download/linux/ubuntu/
> **My solution assumes that you have a user with name=atif and password=atif**
1. ``sudo -u postgres createuser --interactive``
	set role name to **atif**  
2. ``sudo su postgres psql`` this will give psql shell access
3. ``\password atif`` and change password to **atif**
4. ``create database "afinitiTest"``
5. ``\c "afinitiTest"``
6. ``\i ./database.sql``
7. ``select * from "snmpSignals"``
# How to Run the Programme 
In order to run the application you can run the following commands 
1. ``sudo make`` **here sudo is required because it creates a directory in root folder**
This command will compile all the programmes and will produce the following programmes into **/custom-bin/** 
	- Programmes Used By OIDs Extended Using ``extend-sh``  
		 - disk-space-programme 
		 - postgre-query-programme 
	- Programmes Used By OIDs Extended Using ``pass``  
		- disk-space-pass-programme 
		- static-version-pass-programme 
		- postgre-query-pass-programme
	- Subagent Daemon 
		- custom-agent-demon 
	
2. ``sudo ./setup.sh``
This will install all the required dependencies and copy the  required configuration files to the required folders. 
3. Once the setup has been completed now you can access custom OIDs. 
4. now run ``snmpwalk -v2c -c test localhost .1.3.6.1.4.1.53834`` you will see that you have following OIDs available these are from ``extend-sh`` and ``pass`` 


	|           OID     |                               Translated Version                                      |                  
	|----------------|-------------------------------------------------------------------------|
	|.1.3.6.1.4.1.53864.10.0|AFINITI-TASK-MIB::staticProgrammeVersionPass.0  |        
	|.1.3.6.1.4.1.53864.11.0|AFINITI-TASK-MIB::requiredDiskSpaceUsagePass.0 |          
	|.1.3.6.1.4.1.53864.12s.0|AFINITI-TASK-MIB::snmpSignalPass.0                      |

	Following is the image of output. First 3 outputs are from ``pass`` and rest are from ``extend``

	![Output of extend-sh and pass](/img/extend-and-pass-output.png)

5. But the sub agent is also implemented in this solution which is in ``/custom-bin/``
to run this just run the command with ``sudo /custom-bin/custom-agent-demon``	
this will connect sub agent to the master agent and you will have following OIDs available 

	|                 OID              |                                      Translated Version            |                  
	|--------------------------|--------------------------------------------------------|
	|.1.3.6.1.4.1.53864.1.0|AFINITI-TASK-MIB::staticProgrammeVersion.0  |        
	|.1.3.6.1.4.1.53864.2.0|AFINITI-TASK-MIB::requiredDiskSpaceUsage.0 |          
	|.1.3.6.1.4.1.53864.3.0|AFINITI-TASK-MIB::snmpSignal.0|
6. run ``snmpwalk -v2c -c test localhost .1.3.6.1.4.1.53834`` again now you can see OIDs exposed by sub agent as well.

	![Output of extend-sh and pass](/img/subagent-output.png)


# Design
I implemented my solution in C because it is fast and the code I have written for my custom mib modules can be complied directly into the master net-snmp agent. Since I have implemented the required OIDs in 3 ways I have make sure that most of the code is shared among them. This will allow better maintainable code. Also the solution is scalable because you can add as many MIB modules as you want in ``./src/custom-objects`` and register them into ``./src/custom-agent/custom-agent-demon.c``  and on recompilation of the custom agent it will have ability to respond to the OIDs for these MIBs.
## Project Structure
- **include** - contains all include files
- **src** - contains all c files
	- **custom-agent** - contains code for sub agent
	- **custom-objects** - contains MIB modules for custom objects  
	- **helper-programmes** - these are the programs which are used by OIDs registered through ``extend-sh`` in ``snmpd.conf`` file.
	- **pass-programmes**  - these are the programs which will be used by OIDs registered through ``pass`` in ``snmpd.conf`` file. 
	- **utils** - contains all utility code which is shared in the whole project 
## MIBs
This project contains a MIB files named **AFINITI-TASK-MIB**.txt which defines SMIs for all custom OIDs used in this project. You can look into that in this folder. Below is the summary of what the objects and their OIDs it defines and which approach in my solution uses them.

**Following are the OIDs are used by sub agent :** 
|                 OID              |               Translated Version	|                  
|--------------------------|--------------------------------------------|
|.1.3.6.1.4.1.53864.1.0|AFINITI-TASK-MIB::staticProgrammeVersion.0  |        
|.1.3.6.1.4.1.53864.2.0|AFINITI-TASK-MIB::requiredDiskSpaceUsage.0 |          
|.1.3.6.1.4.1.53864.3.0|AFINITI-TASK-MIB::snmpSignal.0|

**Following are the OIDs used by ``pass`` in snmpd.conf:** 
	
|           OID     |                               Translated Version  |                  
|----------------|------------------------------------------------------|
|.1.3.6.1.4.1.53864.10.0|AFINITI-TASK-MIB::staticProgrammeVersionPass.0  |        
|.1.3.6.1.4.1.53864.11.0|AFINITI-TASK-MIB::requiredDiskSpaceUsagePass.0 |          
|.1.3.6.1.4.1.53864.12s.0|AFINITI-TASK-MIB::snmpSignalPass.0                      |

# Testing Methodology
Did unit and functional testing although no script was made or used. 

# Breakdown of the Tasks

|                 Task              |               Time Taken (hrs)	|                  
|--------------------------|--------------------------------------------|
| Research 				|10  |        
|Solution Design Choices |2 |          
|Defining MIBs|0.5|
|Implementation of Util programs|2|
|Implementation of programmes used by extend|1|
|Implementation of programmes used by pass|2|
|Implementation of custom-objects in C using mib2c and sub agent |3|
|Witing script to setup net-snmp|1|
|Witing script to setup database table|1|
|Setups for snmp and postgresql|1|
|Makefile|1|
|README|4|
|Bugfixes and etc |3|
|              Total (hrs)              |              31.5	




# Final discussions and a better approach
After doing research and implementing the solution by using ``extend-sh``, ``pass``, and ``sub-agent (by writing MIB modules in C)`` I found out that 
while it is the easy to extend agent by running arbitrary commands using ``extend-sh`` it is not good when we have our own enterprise number. when we add this number to OID it appends it with `.4.1.2.3` because it is needed to work this extension properly and also converts the name given to this OID to ASCII ask value and cannot be overridden.  

- The better solution to solve this problem we can extend it using ``pass`` which passes the processing control of OID to the provided program and passes OID and some other parameters as arguments. This give a better way to extend this but it is limited by the SNMP Errors it can return and has and reads output  from standard output which can be a problem sometimes because its output should be 3 lines as follows:
	1. OID
	2. return type 
	3. output to be returned 
if output is not in this required form it generates ["This will result in an SNMP _noSuchName_ error, or a _noSuchInstance_ exception".](https://manpages.debian.org/unstable/snmpd/snmpd.conf.5.en.html#MIB-Specific_Extension_Commands) 
- The most reliable solution is to write your own MIB modules in C which give the full control to process the request and generate output and errors if necessary. The best thing about these modules is that they can be either compiled into the source of the master agent or can be compiled into sub agent which can be connected to the master agent or can work independently. I was unable to compile it into master agent but sub agent is included in this repository.

# References:
* https://docstore.mik.ua/orelly/networking_2ndEd/snmp/
* https://nsrc.org/workshops/2015/sanog25-nmm-tutorial/materials/snmp.pdf
* http://monitoringtt.blogspot.com/2010/05/snmp-for-dummies-protocol.html
* https://www.pcwdld.com/what-is-snmp-and-tutorial
* https://eogogics.com/tutorial-simple-network-management-protocol-snmp/
* https://blog.sensu.io/how-to-simplify-snmp-implementation
* https://stackoverflow.com/questions/50648488/how-do-i-build-my-oid-tree-under-my-pen-instead-of-an-extension-of-net-snmp 

