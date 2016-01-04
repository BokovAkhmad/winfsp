#include <winfsp/winfsp.h>
#include <tlib/testsuite.h>

void path_prefix_test(void)
{
    PWSTR ipaths[] =
    {
        L"",
        L"\\",
        L"\\\\",
        L"\\a",
        L"\\\\a",
        L"\\\\a\\",
        L"\\\\a\\\\",
        L"a\\",
        L"a\\\\",
        L"a\\b",
        L"a\\\\b",
        L"foo\\\\\\bar\\\\baz",
        L"foo\\\\\\bar\\\\baz\\",
        L"foo\\\\\\bar\\\\baz\\\\",
    };
    PWSTR opaths[] =
    {
        L"", L"",
        L"", L"",
        L"", L"",
        L"", L"a",
        L"", L"a",
        L"", L"a\\",
        L"", L"a\\\\",
        L"a", L"",
        L"a", L"",
        L"a", L"b",
        L"a", L"b",
        L"foo", L"bar\\\\baz",
        L"foo", L"bar\\\\baz\\",
        L"foo", L"bar\\\\baz\\\\",
    };

    for (size_t i = 0; sizeof ipaths / sizeof ipaths[0] > i; i++)
    {
        PWSTR Prefix, Remain;
        WCHAR buf[32];
        wcscpy_s(buf, 32, ipaths[i]);
        FspPathPrefix(buf, &Prefix, &Remain);
        ASSERT(0 == wcscmp(opaths[2 * i + 0], Prefix));
        ASSERT(0 == wcscmp(opaths[2 * i + 1], Remain));
        FspPathCombine(Prefix, Remain);
        ASSERT(0 == wcscmp(ipaths[i], buf));
    }
}

void path_suffix_test(void)
{
    PWSTR ipaths[] =
    {
        L"",
        L"\\",
        L"\\\\",
        L"\\a",
        L"\\\\a",
        L"\\\\a\\",
        L"\\\\a\\\\",
        L"a\\",
        L"a\\\\",
        L"a\\b",
        L"a\\\\b",
        L"foo\\\\\\bar\\\\baz",
        L"foo\\\\\\bar\\\\baz\\",
        L"foo\\\\\\bar\\\\baz\\\\",
    };
    PWSTR opaths[] =
    {
        L"", L"",
        L"", L"",
        L"", L"",
        L"", L"a",
        L"", L"a",
        L"\\\\a", L"",
        L"\\\\a", L"",
        L"a", L"",
        L"a", L"",
        L"a", L"b",
        L"a", L"b",
        L"foo\\\\\\bar", L"baz",
        L"foo\\\\\\bar\\\\baz", L"",
        L"foo\\\\\\bar\\\\baz", L"",
    };

    for (size_t i = 0; sizeof ipaths / sizeof ipaths[0] > i; i++)
    {
        PWSTR Remain, Suffix;
        WCHAR buf[32];
        wcscpy_s(buf, 32, ipaths[i]);
        FspPathSuffix(buf, &Remain, &Suffix);
        ASSERT(0 == wcscmp(opaths[2 * i + 0], Remain));
        ASSERT(0 == wcscmp(opaths[2 * i + 1], Suffix));
        FspPathCombine(Remain, Suffix);
        ASSERT(0 == wcscmp(ipaths[i], buf));
    }
}

void path_tests(void)
{
    TEST(path_prefix_test);
    TEST(path_suffix_test);
}