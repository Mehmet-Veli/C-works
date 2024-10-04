#include <assert.h>
#include <stdio.h>
#include <string.h>

void string_to_hexadecimal(const char* in, char* out)
{
    int len = strlen(in);
    for (int i = 0; i < len; ++i)
    {
        sprintf(out + (i * 2), "%02x", (unsigned char)in[i]);
    }
    out[len * 2] = '\0';
}

void test()
{
    // given
    const char* in = "Lorem Ipsum is simply dummy text!";
    char out[100] = {0};

    // when
    string_to_hexadecimal(in, out);

    // then
    // printf("%s\n", out);
    assert(strcmp("4c6f72656d20497073756d2069732073696d706c792064756d6d79207465787421",
                  out) == 0);
}

int main()
{
    test();
    return 0;
}