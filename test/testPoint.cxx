#define BOOST_TEST_MODULE Test InfluxDB Point
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../include/InfluxDBFactory.h"

namespace influxdb {
namespace test {


std::vector<std::string> getVector(const Point& point)
{
  std::istringstream result(point.toLineProtocol());
  return std::vector<std::string>{std::istream_iterator<std::string>{result},
                      std::istream_iterator<std::string>{}};
}

BOOST_AUTO_TEST_CASE(test1)
{
  auto point = Point{"test"}
    .addField("value", 10);

  auto result = getVector(point);

  BOOST_CHECK_EQUAL(result[0], "test");
  BOOST_CHECK_EQUAL(result[1], "value=10i");
}

BOOST_AUTO_TEST_CASE(test2)
{
  auto point = Point{"test"}
    .addField("value", 10)
    .addField("dvalue", 10.10);

  auto result = getVector(point);

  BOOST_CHECK_EQUAL(result[0], "test");
  BOOST_CHECK_EQUAL(result[1], "value=10i,dvalue=10.1");
}

BOOST_AUTO_TEST_CASE(test3)
{
  auto point = Point{"test"}
    .addField("value", 10)
    .addField("dvalue", 10.10)
    .addTag("tag", "tagval");

  auto result = getVector(point);

  BOOST_CHECK_EQUAL(result[0], "test,tag=tagval");
  BOOST_CHECK_EQUAL(result[1], "value=10i,dvalue=10.1");
}


} // namespace test
} // namespace influxdb
