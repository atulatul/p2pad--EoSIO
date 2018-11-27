//p2pad.cpp

#include "p2pad.hpp"

// note I  use print to help in checking 

// public methods exposed via the ABI



void p2pad::version() {
    eosio::print("p2pad version  0.1! Created No testing Yet"); 
};

void p2pad::addad(eosio::name s,std::string adName, std::string adURL,uint64_t type,uint32_t totalTok,uint32_t tokenPerUser,uint8_t status,std::string lat, std::string longi) {
    require_auth(s);
//TO-DO for testing left without permission check need to add permission like p2pad @require
    //symbol_type symbol(S(4,SYS));
    //accounts fromAcc(N(eosio.token),N(s));
   // const auto& myAcc = fromAcc.get(symbol.name());
  //  myAcc.balance.print();

    eosio::print("Add new advertisement ", adName); 
    
    // update the table to include a new Advertisement
    _ads.emplace(get_self(), [&](auto& p) {
        p.key = _ads.available_primary_key();
        p.adId = _ads.available_primary_key();
        p.adCategory = type;
        p.adName = adName;
        p.adURI = adURL;
        p.adStatus = 0;
        p.totolToken = totalTok;
        p.tokenPerWatch = tokenPerUser;
        p.latitude = lat;
        p.longitude = longi;

    });
}

void p2pad::adstatus(std::string adName) {
    eosio::print("Change ad status ", adName);

    std::vector<uint64_t> keysForModify;
    // find items which are for the named poll
    for(auto& item : _ads) {
        if (item.adName == adName) {
            keysForModify.push_back(item.key);   
        }
    }
    
    // now get each item and modify the status
    for (uint64_t key : keysForModify) {
        eosio::print("modify _ads status", key);
        auto itr = _ads.find(key);
        if (itr != _ads.end()) {
            _ads.modify(itr, get_self(), [&](auto& p) {
                p.adStatus = p.adStatus + 1;
            });
        }
    }
}

void p2pad::adreset(std::string adName) {
    eosio::print("Reset ad status ", adName); 
//TO-DO for testing left without permission check need to add permission like p2pad @require
    std::vector<uint64_t> keysForModify;
    // find all poll items
    for(auto& item : _ads) {
        if (item.adName == adName) {
            keysForModify.push_back(item.key);   
        }
    }
    
    // update the status in each poll item
    for (uint64_t key : keysForModify) {
        eosio::print("modify _ads status", key);
        auto itr = _ads.find(key);
        if (itr != _ads.end()) {
            _ads.modify(itr, get_self(), [&](auto& p) {
                p.adStatus = 0;
            });
        }
    }
}



void p2pad::viewad(std::string adName, std::string accountName)
{
    eosio::print("view for ad ", adName, " by ", accountName); 

    // is the ad open
    for(auto& item : _ads) {
        if (item.adName == adName) {
            if (item.adStatus != 1 || item.totolToken<=0) {
                eosio::print("ad ",adName,  " is not open or no more token left for the ad");
                return;
            }
            break; // only need to check status and  once
        }
    }

    // has account name already viewed?  
    for(auto& view : _views) {
        if (view.adName == adName && view.account == accountName) {
            eosio::print(accountName, " has already viewed ad ", adName);
            //eosio_assert(true, "Already Voted");
            return;
        }
    }

    uint64_t adId =99999; // get the addId for the _ads table

    // find the poll and the option and increment the count
    for(auto& item : _ads) {
        if (item.adName == adName) {
            adId = item.adId; // for recording view in this ad
            _ads.modify(item, get_self(), [&](auto& p) {
                p.totolToken = p.totolToken - p.tokenPerWatch;
            });
        }
    }

    // record that accountName has viewed
        _views.emplace(get_self(), [&](auto& pv){
        pv.key = _ads.available_primary_key();
        pv.adId = adId;
        pv.adName = adName;
        pv.account = accountName;
    });        
}
//right now dont worry much about lat long etc... just check based on the category and retunr the same
void p2pad::getad(uint64_t category,std::string latitude, std::string longitude,int minPrice,int maxPrice){

std::vector<uint64_t> keysForRes;
// is the ad open
    for(auto& item : _ads) {
        if (item.adCategory == category && item.adStatus ==1 && item.totolToken>0) {
            keysForRes.push_back(item.key);
        }
    }


    // print the ads in the command line the adName and URL
    for (uint64_t key : keysForRes) {
        eosio::print("selecting ads for getad response", key);
        auto itr = _ads.find(key);
        if (itr != _ads.end()) {
            eosio::print("Sending ad Name:",itr->adName,"==>", itr->adURI);
            }
        }
}


EOSIO_DISPATCH( p2pad, (version)(addad)(adstatus)(adreset)(viewad)(getad))
