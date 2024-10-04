#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void hexadecimal_to_string(const char* in, char* out)
{
    uint8_t len = strlen(in);
    for (int i = 0; i < len; i += 2)
    {
        char msb = (in[i] <= '9') ? in[i] - '0'
                                  : (in[i] & 0x5F) - 'A' + 10;
        char lsb = (in[i + 1] <= '9') ? in[i + 1] - '0'
                                      : (in[i + 1] & 0x5F) - 'A' + 10;
        out[i / 2] = (msb << 4) | lsb;
    }
    out[len / 2] = '\0';
}

void test()
{
    // given
    const char* in =
        "4c6f72656d20497073756d2069732073696d706c792064756d6d79207465787421";
    char out[100] = {0};

    // when
    hexadecimal_to_string(in, out);

    // then
    // printf("%s\n", out);
    assert(strcmp("Lorem Ipsum is simply dummy text!", out) == 0);
}

int main()
{
    test();
    return 0;
}