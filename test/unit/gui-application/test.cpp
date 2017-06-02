//
// Created by zhanggyb on 16-9-19.
//

#include "test.hpp"

#include <skland/gui/application.hpp>

using skland::Application;

Test::Test()
    : testing::Test() {
}

Test::~Test() {

}

/*
 *
 */
TEST_F(Test, application) {
  int argc = 1;
  char argv1[] = "application";  // to avoid compile warning
  char *argv[] = {argv1};

  Application app(argc, argv);

  bool result1 = (app.GetArgc() == argc);
  bool result2 = (strcmp(app.GetArgv()[0], argv1) == 0);

  app.Exit();

  ASSERT_TRUE(result1 && result2);
}
