#include <cppunit/extensions/HelperMacros.h>
#include <sstream>
#include "testUtil.h"
#include "librets/CapabilityUrls.h"

using namespace librets;
using namespace std;

#define CLASS CapabilityUrlsTest

class CLASS : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(CLASS);
    CPPUNIT_TEST(testResolvingUrls);
    CPPUNIT_TEST(testEquals);
    CPPUNIT_TEST_SUITE_END();

  protected:
    void testResolvingUrls();
    void testEquals();

    string getBase();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CLASS);

string CLASS::getBase()
{
    return "http://example.com:6103";
}

void CLASS::testResolvingUrls()
{
    CapabilityUrls urls(getBase() + "/rets/login");
    urls.SetActionUrl("");
    urls.SetChangePasswordUrl(getBase() + "/rets/changePassword");
    urls.SetGetObjectUrl("/rets/getObject");
    urls.SetSearchUrl("search");
    ASSERT_STRING_EQUAL("", urls.GetActionUrl());
    ASSERT_STRING_EQUAL("http://example.com:6103/rets/changePassword",
                        urls.GetChangePasswordUrl());
    ASSERT_STRING_EQUAL("http://example.com:6103/rets/getObject",
                        urls.GetGetObjectUrl());
    ASSERT_STRING_EQUAL("http://example.com:6103/rets/search",
                        urls.GetSearchUrl());
}

void CLASS::testEquals()
{
    CapabilityUrls cu1(getBase() + "/rets/login");
    cu1.SetActionUrl(getBase() + "/rets/action");
    cu1.SetChangePasswordUrl(getBase() + "/rets/changePassword");
    cu1.SetGetObjectUrl(getBase() + "/rets/getObject");
    cu1.SetLoginUrl(getBase() + "/rets/login");
    cu1.SetLoginCompleteUrl(getBase() + "/rets/loginComplete");
    cu1.SetLogoutUrl(getBase() + "/rets/logout");
    cu1.SetSearchUrl(getBase() + "/rets/search");
    cu1.SetGetMetadataUrl(getBase() + "/rets/getMetadata");
    cu1.SetServerInformationUrl(getBase() + "/rets/serverInfo");
    cu1.SetUpdateUrl(getBase() + "/rets/update");

    CapabilityUrls cu2(getBase() + "/rets/login");
    cu2.SetActionUrl(getBase() + "/rets/action");
    cu2.SetChangePasswordUrl(getBase() + "/rets/changePassword");
    cu2.SetGetObjectUrl(getBase() + "/rets/getObject");
    cu2.SetLoginUrl(getBase() + "/rets/login");
    cu2.SetLoginCompleteUrl(getBase() + "/rets/loginComplete");
    cu2.SetLogoutUrl(getBase() + "/rets/logout");
    cu2.SetSearchUrl(getBase() + "/rets/search");
    cu2.SetGetMetadataUrl(getBase() + "/rets/getMetadata");
    cu2.SetServerInformationUrl(getBase() + "/rets/serverInfo");
    cu2.SetUpdateUrl(getBase() + "/rets/update");

    CapabilityUrls cu3(getBase() + "/rets/login");
    cu3.SetActionUrl("/rets/action");
    cu3.SetChangePasswordUrl("/rets/changePassword");
    cu3.SetGetObjectUrl("/rets/getObject");
    cu3.SetLoginUrl(getBase() + "/rets/login");
    cu3.SetLoginCompleteUrl("/rets/loginComplete");
    cu3.SetLogoutUrl("/rets/logout");
    cu3.SetSearchUrl("/rets/search");
    cu3.SetGetMetadataUrl("/rets/getMetadata");
    cu3.SetServerInformationUrl("/rets/serverInfo");
    cu3.SetUpdateUrl("/rets/update");

    CPPUNIT_ASSERT_EQUAL(cu1, cu2);
    CPPUNIT_ASSERT_EQUAL(cu1, cu3);
}
