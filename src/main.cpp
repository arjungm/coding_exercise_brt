#include "Browser.hpp"
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;

int main(int argc, char** argv)
{
  SystemBrowser browser;
  browser.loadFromFile("countries.sx");
  browser.run();
  
  // boost bind shenanigans
  boost::function<void(int i, const string& s)> myFunctionObject = boost::bind(&SystemBrowser::printThings, &browser, _2, _1);
  boost::function<void(int i)> myBakedInFunctionObject = boost::bind(&SystemBrowser::printThings, &browser, ":countries", _1);

  // testing
  browser.printThings(":countries", 1);
  myFunctionObject(1,":countries");
  myBakedInFunctionObject(1);
  cout << endl;
  browser.printThings(":countries", 6);
  myFunctionObject(6,":countries");
  myBakedInFunctionObject(6);

  return 0;
}
