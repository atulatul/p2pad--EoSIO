
// this is the header file p2pad.hpp

#pragma once

#include <eosiolib/eosio.hpp>
//#include <eosio.token/eosio.token.hpp>
//using namespace eosio; -- not using this so you can explicitly see which eosio functions are used.

class [[eosio::contract]] p2pad : public eosio::contract {

public:

    //using contract::contract;

    p2pad( eosio::name receiver, eosio::name code, eosio::datastream<const char*> ds ): eosio::contract(receiver, code, ds),  _ads(receiver, code.value), _views(receiver, code.value)
    {}

    // [[eosio::action]] will tell eosio-cpp that the function is to be exposed as an action for user of the smart contract.
    [[eosio::action]] void version();
    [[eosio::action]] void addad(eosio::name s,std::string adName, std::string adURL,uint64_t type,uint32_t totalTok,uint32_t tokenPerUser,uint8_t status,std::string lat,std::string longi);
    // TO-DO [[eosio::action]] void rmadvertisement(eosio::name s, std::string adName);
    [[eosio::action]] void adstatus(std::string adName);
    [[eosio::action]] void adreset(std::string pollName);
    [[eosio::action]] void viewad(std::string pollName, std::string accountName);
    [[eosio::action]] void getad(uint64_t category,std::string latitude, std::string longitude,int minPrice,int maxPrice);
    //this method can be modified to include more information/s.

    //private: -- not private so the cleos get table call can see the table data.

    // create the multi index tables to store the data
    struct [[eosio::table]] advert 
    {
        uint64_t      key; // primary key
        uint64_t      adId; // second key, non-unique, this table will have dup rows for each poll because of option
        std::string   adName; // name of ad
        std::string   adURI; // uri where to hit to receive read/listen/view the ad it would be tiny URI in product to save RAM
        uint64_t      adCategory =0; //add category as of now lets concentrate on movie 0= action, 1 = comedy, 2 = fiction, 3 = romance
        uint8_t       adStatus =0; // staus where 0 = closed, 1 = open, 2 = finished
        uint32_t      totolToken =0; // the token supply for the current ad it will keep reducing once user keep watching and add will stop once 0
        uint32_t      tokenPerWatch = 10; //this the comapny which is adding add can decide and can be available to end user
        std::string   latitude;//for localization facility
        std::string   longitude ;//for localization facility

        uint64_t primary_key() const { return key; }
        uint64_t by_adId() const {return adId;}
    };
    typedef eosio::multi_index<"advert"_n, advert, eosio::indexed_by<"adid"_n, eosio::const_mem_fun<advert, uint64_t, &advert::by_adId>>> adstable;

    struct [[eosio::table]] adviews 
    {
        uint64_t     key; 
        uint64_t     adId;
        std::string  adName; // name of ad
        std::string  account; //this account has viewed, use this to make sure noone view > 1

        uint64_t primary_key() const { return key; }
        uint64_t by_adId() const {return adId; }
    };
    typedef eosio::multi_index<"adviews"_n, adviews, eosio::indexed_by<"adid"_n, eosio::const_mem_fun<adviews, uint64_t, &adviews::by_adId>>> views;

    //struct account {
   //     asset    balance;
    //    uint64_t primary_key()const { return balance.symbol.name(); }
  //   };

    //typedef eosio::multi_index<N(accounts), account> accounts;

    //// local instances of the multi indexes
    adstable _ads;
    views _views;
};
