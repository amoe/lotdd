googletest_framework_root = "/home/amoe/vcs/googletest"

googletest_include_paths = [
    googletest_framework_root + "/googletest",
    googletest_framework_root + "/googletest/include",
    googletest_framework_root + "/googlemock",
    googletest_framework_root + "/googlemock/include"
]

gtest_all_path = googletest_framework_root + "/googletest/src/gtest-all.cc"

env = Environment(CPPPATH=googletest_include_paths)

env.Program(
    target='main',
    source=["main.cc", gtest_all_path],
    LIBS=['pthread']
)
