// Example program
#include <iostream>
#include <string>

class MarketDataProxy {
  public:
    virtual const char* get_code() const {
        return "";
    }
    virtual double get_ask_price_1() const {
        return (double)0;
    }
    virtual double get_ask_price_2() const {
        return (double)0;
    }
    virtual double get_ask_price_3() const {
        return (double)0;
    }
    virtual double get_ask_price_4() const {
        return (double)0;
    }
    virtual double get_ask_price_5() const {
        return (double)0;
    }
    virtual double get_ask_volume_1() const {
        return (double)0;
    }
    virtual double get_ask_volume_2() const {
        return (double)0;
    }
    virtual double get_ask_volume_3() const {
        return (double)0;
    }
    virtual double get_ask_volume_4() const {
        return (double)0;
    }
    virtual double get_ask_volume_5() const {
        return (double)0;
    }
    virtual double get_bid_price_1() const {
        return (double)0;
    }
    virtual double get_bid_price_2() const {
        return (double)0;
    }
    virtual double get_bid_price_3() const {
        return (double)0;
    }
    virtual double get_bid_price_4() const {
        return (double)0;
    }
    virtual double get_bid_price_5() const {
        return (double)0;
    }
};

struct MarketDataA {
    char instrumentId[20];  //股票代码
    double askPrice1;       //申卖价一
    uint64_t askVolume1;    //申卖量一
    double bidPrice1;       //申买价一
    uint64_t bidVolume1;    //申买量一
    double askPrice2;       //申卖价二
    uint64_t askVolume2;    //申卖量二
    double bidPrice2;       //申买价二
    uint64_t bidVolume2;    //申买量二
    double askPrice3;       //申卖价三
    uint64_t askVolume3;    //申卖量三
    double bidPrice3;       //申买价三
    uint64_t bidVolume3;    //申买量三
    double askPrice4;       //申卖价四
    uint64_t askVolume4;    //申卖量四
    double bidPrice4;       //申买价四
    uint64_t bidVolume4;    //申买量四
    double askPrice5;       //申卖价五
    uint64_t askVolume5;    //申卖量五
    double bidPrice5;       //申买价五
    uint64_t bidVolume5;    //申买量五
};
class MarketDataAProxy : public MarketDataProxy {
public:
    MarketDataA market_data_a;
    const char* get_code() const override {
        return market_data_a.instrumentId;
    }
    double get_ask_price_1 () const override {
        return market_data_a.askPrice1;
    }
    double get_bid_price_1 () const override {
        return market_data_a.bidPrice1;
    }
};
struct MarketDataB {
    std::string code;       //股票代码
    double askPrice[5];     //申卖价
    uint64_t askVolume[5];  //申卖量
    double bidPrice[5];     //申买价
    uint64_t bidVolume[5];  //申买量
};
class MarketDataBProxy : public MarketDataProxy {
public:
    MarketDataB market_data_b;
    const char* get_code() const override {
        return market_data_b.code.c_str();
    }
    double get_ask_price_1 () const override {
        return market_data_b.askPrice[0];
    }
    double get_bid_price_1 () const override {
        return market_data_b.bidPrice[0];
    }
};



void printMidPrice(const MarketDataProxy& market_data_proxy) {
    std::cout << (market_data_proxy.get_ask_price_1() + market_data_proxy.get_bid_price_1()) / 2;
}

int main()
{
}
