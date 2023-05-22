/*
     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


*/

#include <cassert>
#include "Aria/Aria.h"

void test_escape_space(const char *str, const char *expected)
{
  printf("Escaping spaces from input string: \"%s\"\n", str);
  constexpr size_t bufferlen = 512;
  char buffer[bufferlen];
  ArUtil::escapeSpaces(buffer, str, bufferlen);
  printf("\t...after escaping spaces: \"%s\"\n", buffer);
  assert(strcmp(buffer, expected) == 0);
}

void printbuf(char *buf1)
{
    printf("buf=%x('%c') %x('%c') %x('%c') %x('%c') %x('%c')\n", buf1[0], buf1[0], buf1[1], buf1[1], buf1[2], buf1[2], buf1[3], buf1[3], buf1[4], buf1[4]);
}

void testCopyStringToBuffer()
{
    char buf1[5];
    memset(buf1, ' ', 5);

    char buf2[5];
    buf2[0] = 'A';
    buf2[1] = 'B';
    buf2[2] = 'C';
    buf2[3] = 'D';
    buf2[4] = '\0';

    ArUtil::copy_string_to_buffer(buf1, 5, buf2, 5);
    printbuf(buf1);
    assert(strcmp(buf1, "ABCD") == 0);

    memset(buf1, ' ', 5);
    ArUtil::copy_string_to_buffer(buf1, 5, buf2, 3);
    printbuf(buf1);
    assert(strcmp(buf1, "ABC") == 0);

    memset(buf1, ' ', 5);
    ArUtil::copy_string_to_buffer(buf1, 5, buf2, 8);
    printbuf(buf1);
    assert(strcmp(buf1, "ABCD") == 0);

    memset(buf1, ' ', 5);
    ArUtil::copy_string_to_buffer(buf1, buf2, 5);
    printbuf(buf1);
    assert(strcmp(buf1, "ABCD") == 0);

    memset(buf1, ' ', 5);
    ArUtil::copy_string_to_buffer(buf1, buf2, 3); // assume destbuf has size 3. last char buf1[2] should be set to null.
    printbuf(buf1);
    assert(buf1[2] == '\0');
    assert(strcmp(buf1, "AB") == 0);

}


int main()
{
  test_escape_space("", "");
  test_escape_space(" ", "\\ ");
  test_escape_space("  ", "\\ \\ ");
  test_escape_space("hi", "hi");
  test_escape_space("boy oh boy is this fun!", "boy\\ oh\\ boy\\ is\\ this\\ fun!");

  // should truncate because buffer is too small:
  constexpr size_t smallbufferlen = 8;
  char smallbuffer[smallbufferlen];
  ArUtil::escapeSpaces(smallbuffer, "hello world", smallbufferlen);
  printf("escapeSpaces() with small buffer (%lu) => \"%s\"\n", smallbufferlen, smallbuffer);
  assert(strcmp(smallbuffer, "hello\\ ") == 0);
  puts("\t...ok.\n");


  puts("ArUtil::lower()...");
  constexpr size_t bufferlen = 512;
  char buffer[bufferlen];
  ArUtil::lower(buffer, "TEST", bufferlen);
  assert(strcmp(buffer, "test") == 0);

  ArUtil::lower(buffer, "test", bufferlen);
  assert(strcmp(buffer, "test") == 0);

  ArUtil::lower(buffer, "", bufferlen);
  assert(strcmp(buffer, "") == 0);

  ArUtil::lower(buffer, "another TEST string!", bufferlen);
  assert(strcmp(buffer, "another test string!") == 0);
  puts("\t...ok\n");


  puts("ArUtil::isOnlyAlphaNumeric()...");
  assert(ArUtil::isOnlyAlphaNumeric("abc123") == true);
  assert(ArUtil::isOnlyAlphaNumeric("abc 123") == false); // spaces are not allowed
  assert(ArUtil::isOnlyAlphaNumeric("abc\t123") == false); // spaces are not allowed
  assert(ArUtil::isOnlyAlphaNumeric("") == true);
  assert(ArUtil::isOnlyAlphaNumeric("abc123!") == false);
  assert(ArUtil::isOnlyAlphaNumeric("abc\n123") == false);
  assert(ArUtil::isOnlyAlphaNumeric("\n") == false);
  assert(ArUtil::isOnlyAlphaNumeric("\r") == false);
  assert(ArUtil::isOnlyAlphaNumeric("+23") == true); // + should be allowed
  assert(ArUtil::isOnlyAlphaNumeric("-42") == true); // - should be allowed
  assert(ArUtil::isOnlyAlphaNumeric("-42.00") == false); // . should not be allowed
  assert(ArUtil::isOnlyAlphaNumeric("23,00") == false); // , should not be allowed
  puts("\t...ok\n");

  puts("ArUtil::isOnlyNumeric()...");
  assert(ArUtil::isOnlyNumeric("123") == true);
  assert(ArUtil::isOnlyNumeric("abc") == false);
  assert(ArUtil::isOnlyNumeric("+1") == true);
  assert(ArUtil::isOnlyNumeric("-1") == true);
  assert(ArUtil::isOnlyNumeric("3.1415") == false);
  assert(ArUtil::isOnlyNumeric("1 2 3") == false);
  assert(ArUtil::isOnlyNumeric("") == true);
  puts("\t...ok\n");

  puts("parsing and converting strings/numbers...");

  bool ok = false;
  double d = ArUtil::readDoubleValue("0.0", &ok);
  assert(ok);
  assert(d == 0.0);

  d = ArUtil::readDoubleValue("23", &ok);
  assert(ok);
  assert(d == 23);

  d = ArUtil::readDoubleValue("", &ok);
  assert(!ok);

  d = ArUtil::readDoubleValue("abc", &ok);
  assert(!ok);

  assert(strcmp(ArUtil::convertBool(true), "true") == 0);
  assert(strcmp(ArUtil::convertBool(9), "true") == 0);
  assert(strcmp(ArUtil::convertBool(false), "false") == 0);
  assert(strcmp(ArUtil::convertBool(0), "false") == 0);

  puts("\t...ok\n");


  testCopyStringToBuffer();



  puts("moreStringTests done.");
  return 0;
}
