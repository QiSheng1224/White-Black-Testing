#include "gtest/gtest.h"
#include "date.h"

class DateTest : public ::testing::Test {
 public:
  void SetUp( ) { 
    // code here will execute just before the test ensues 
	  first_day = Date(2018, 9, 4);
    last_day = Date(2018, 12, 11);
    y2k = Date(1999, 12, 31);
    ind_day = Date(1776, 7, 4);
    halloween = Date(2018, 10, 31);
    epoch = Date(0);
    today = Date();
  }
  protected:
    Date first_day;
    Date last_day;
    Date y2k;
    Date ind_day;
    Date halloween;
    Date epoch;
    Date today;
};

TEST_F(DateTest, PrintDateTests) {
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween
  
  std::string expected_out_1 = "1999-12-31\n";
  std::string expected_out_2 = "1776-07-04\n";
  std::string expected_out_3 = "2018-10-31\n";
  
  testing::internal::CaptureStdout();
  y2k.PrintDate(true);
  std::string output1 = testing::internal::GetCapturedStdout();
  
  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  ind_day.PrintDate(true);
  std::string output2 = testing::internal::GetCapturedStdout();
  
  testing::internal::CaptureStdout();
  best_holiday.PrintDate(true);
  std::string output3 = testing::internal::GetCapturedStdout();
  
  EXPECT_EQ(output1, expected_out_1);
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(output3, expected_out_3);
}

TEST_F(DateTest, PrintDateTestsWithoutNewline) {
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween
  
  std::string expected_out_1 = "1999-12-31";
  std::string expected_out_2 = "1776-07-04";
  std::string expected_out_3 = "2018-10-31";
  
  testing::internal::CaptureStdout();
  y2k.PrintDate(false);
  std::string output1 = testing::internal::GetCapturedStdout();
  
  testing::internal::CaptureStdout();
  ind_day.PrintDate(false);
  std::string output2 = testing::internal::GetCapturedStdout();
  
  testing::internal::CaptureStdout();
  best_holiday.PrintDate(false);
  std::string output3 = testing::internal::GetCapturedStdout();
  
  EXPECT_EQ(output1, expected_out_1);
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(output3, expected_out_3);
}

/**
  *
  * Note, this is the only provided test case which actually uses our test fixture
  * 
  * However, it is illegal to mix TEST() and TEST_F() in the same test case (file).
  *
  */
  
TEST_F(DateTest, DaysBetweenTests) {
  EXPECT_EQ(first_day.GetUsDate(), "09-04-2018") << "First day of class not setup properly";
  EXPECT_EQ(last_day.GetUsDate(), "12-11-2018") << "Last day of class not setup properly";
  EXPECT_EQ(first_day.DaysBetween(last_day), 98) << "Days between is not calculated properly";
}

/**
  *
  * NOPE!  Can't test PRIVATE methods
  *
  */
/*
TEST(DateTest, ConvertFromDays) {
	Date convert_first_day = ConvertToDays(2458365);
	EXPECT_STREQ(convert_first_day.GetUsDate(), "09-04-2018");
}
*/

TEST_F(DateTest, SubtractOverload) {
  Date day(2016, 3, 1);
  day = day - 2;
  std::string expected_out_1 = "2016-02-28\n";

  testing::internal::CaptureStdout();
  day.PrintDate(true);
  std::string output_1 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output_1, expected_out_1);
}

TEST_F(DateTest, AddOverload) {
  Date day(2016, 2, 27);

  day = day + 2;
  std::string expected_out_1 = "2016-02-29\n";

  testing::internal::CaptureStdout();
  day.PrintDate(true);
  std::string output_1 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output_1, expected_out_1);
}

TEST_F(DateTest, LeadingZero) {
  std::time_t t = std::time(0);
  std::tm* now = std::localtime(&t);
  char expected_out_1[50];
  sprintf(expected_out_1, "%02d-%02d-%04d", now->tm_mon + 1, now->tm_mday, now->tm_year + 1900);

  testing::internal::CaptureStdout();
  today.PrintUsDate(false);
  std::string output_1 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output_1, expected_out_1);
}

TEST_F(DateTest, TodayDateMonth) {
  std::time_t t = std::time(0);
  std::tm* now = std::localtime(&t);
  char expected_out_1[50];
  sprintf(expected_out_1, "%04d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);

  testing::internal::CaptureStdout();
  today.PrintDate(false);
  std::string output_1 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output_1, expected_out_1);
}

TEST_F(DateTest, DaysBetweenTwoDays) {
  Date day1(2016, 1, 1);
  Date day2(2016, 3, 1);

  EXPECT_EQ(day1.DaysBetween(day2), 60);
}

TEST_F(DateTest, EpochDates) {
  std::string expected_out_1 = "1970-01-01\n";

  testing::internal::CaptureStdout();
  epoch.PrintDate(true);
  std::string output_1 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output_1, expected_out_1);
}

TEST_F(DateTest, GetDates) {
  std::string expected_out_1 = "2018-09-04";

  EXPECT_EQ(first_day.GetDate(), expected_out_1);
}