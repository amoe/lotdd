googletest_framework_root = "/home/amoe/vcs/googletest"

googletest_include_paths = [
    googletest_framework_root + "/googletest",
    googletest_framework_root + "/googletest/include",
    googletest_framework_root + "/googlemock",
    googletest_framework_root + "/googlemock/include"
]

gtest_all_path = googletest_framework_root + "/googletest/src/gtest-all.cc"
gmock_all_path = googletest_framework_root + "/googlemock/src/gmock-all.cc"

env = Environment(CPPPATH=googletest_include_paths)

env.Program(
    target='main',
    source=["main.cc", "soundex_test.cc", gtest_all_path, gmock_all_path],
    LIBS=['pthread']
)
