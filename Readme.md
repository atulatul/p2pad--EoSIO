# Decentralized P2P Ad Framework

This project will create a DApp by using P2P Ad Framework contract based on EOSIO(C++).

This is initial version of the contract and it will have a full ux interface added to it in the next update using which the end user and  product or service proivder can directly place their ad on the blockchain and get connected with end user as their partner.*abi,.wast.wasm added for end user to verify if they are checking p2pad on their machine and verify build and contribute in ux in case interested.**This code does not include ricardian_clauses.**  
## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.  

### Prerequisites

Follow steps mentioned to install development environment https://developers.eos.io/eosio-home/docs/introduction  

### Configuring project

- Copy attached files from under current dir(you may create new dir and change dir to the new dir before running below mentioned commands  
...
use commands mentioned on the aforemnetioned link to deploy the contract on the local network and then call the actions using command line till the UX is updated.
...
## Testing

To test code:  
1: Copy the code into the contracts directory with folder name p2pad  
2: use command to create key "cleos create account eosio p2pad EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV -p eosio@active"  [Use your own wallet key instead mentioned here]
3: abgigen for contract atul2@atul2-VirtualBox:~/contracts/p2pad$ eosio-cpp -o p2pad.wasm p2pad.cpp --abigen  
4: atul2@atul2-VirtualBox:~/contracts$ cleos set contract p2pad1 /home/atul2/contracts/p2pad -p p2pad1@active
Reading WASM from /home/atul2/contracts/p2pad/p2pad.wasm...
Publishing contract...
executed transaction: 01a037922edbe3452fcf8b3f34ef93ab361c0495db5fdec81e9ff90864bd9056  9928 bytes  16894 us
#         eosio <= eosio::setcode               {"account":"p2pad1","vmtype":0,"vmversion":0,"code":"0061736d0100000001c8011e60017f0060027f7f0060037...
#         eosio <= eosio::setabi                {"account":"p2pad1","abi":"0e656f73696f3a3a6162692f312e30000805616464616400090173046e616d650661644e6...
warning: transaction executed locally, but may not be confirmed by the network yet         ] 
5: Call methods as follows to test:
   for method addad: 
   
     atul2@atul2-VirtualBox:~/contracts/p2pad$ cleos push action p2pad1 addad '["p2pad1","myAd1","http://youtube.com/dsddf",0,1000,10,1,"11.23","12.22"]' -p p2pad1@active
executed transaction: 2b16e6441559801954999c6880b3733a3052c12ed956ee219b2c6cb41a0f6ddb  160 bytes  2577 us
#        p2pad1 <= p2pad1::addad                {"s":"p2pad1","adName":"myAd1","adURL":"http://youtube.com/dsddf","type":0,"totalTok":1000,"tokenPer...
>> Add new advertisement myAd1
warning: transaction executed locally, but may not be confirmed by the network yet         ] 

to call adstatus

atul2@atul2-VirtualBox:~/contracts/p2pad$ cleos push action p2pad1 adstatus '["myAd1"]' -p p2pad1@active
executed transaction: 59543fa348edadb20cf15ca5c4b8d3db96ca46edfd7a7e8a5b9490b44be0859c  104 bytes  2741 us
#        p2pad1 <= p2pad1::adstatus             {"adName":"myAd1"}
>> Change ad status myAd1modify _ads status1
warning: transaction executed locally, but may not be confirmed by the network yet         ] 

to call getad [based on adcategory here it would 0 as we created ad with category 0 in addad method call]

to call getad:

atul2@atul2-VirtualBox:~/contracts/p2pad$ cleos push action p2pad1 getad '[0,"11.12","12.12",10,100]' -p p2pad1@active
executed transaction: 498483e4eb7554bef721db81f81d4654c90ebdd08176854cf10b3841a5b27cac  120 bytes  2424 us
#        p2pad1 <= p2pad1::getad                {"category":0,"latitude":"11.12","longitude":"12.12","minPrice":10,"maxPrice":100}
>> selecting ads for getad response1Sending ad Name:myAd1==>http://youtube.com/dsddf
warning: transaction executed locally, but may not be confirmed by the network yet         ] 



Copywrite : All Rights for this code and idea is reserved with the author and whitout any prior permission or any prior date evidence [GIT/or other valid platform] of similar idea by other person organization any alteration or utilization of the code/idea is not permitted.
