#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <string.h>

#include "pa2.h"
#include "test.h"

#define SYSRUN(CMD) (system(CMD))

char* refFileName = ".test_displayLights_reference_file";
char* testFileName = ".test_displayLights_student_file";

/* Function Name: writeRefFile
 * Description:   Takes a string as input.  Re-opens file specified by
 *                refFileName and writes the input string plus a newline
 *                to the reference file.
 */
void writeRefFile(char* str) {
  FILE* f = fopen(refFileName, "w");
  if (f == NULL) {
    perror("Could not open reference file for writing");
    exit(1);
  }

  fwrite(str, 1, strlen(str), f);
  fwrite("\n", 1, 1, f);

  fclose(f);
}

/* Function Name: runTest
 * Description:   Helper function to actually run a test of displayLights.
 *                Prints test description (as specified by testDesc), and
 *                calls displayLights, handling segfaults.
 */
void runTest(unsigned int bank[], char* expectedOutput, char* testDesc) {


  /* Begin setup to capture stdout to a file */
  FILE* testFilePtr = fopen(testFileName, "w");
  if (testFilePtr == NULL) {
    perror("Could not open test file");
    exit(1);
  }

  if (dup2(fileno(testFilePtr), fileno(stdout)) == -1) {
    perror("Could not duplicate stdout file descriptor");
    exit(1);
  }
  /* End setup to capture stdout */

  char cmdstr[BUFSIZ];
  (void) snprintf(cmdstr, BUFSIZ, "diff -b %s %s", testFileName, refFileName);
  fprintf(stderr, "\n%s\n", testDesc);

  displayLights(bank);
  fflush(stdout);
  writeRefFile(expectedOutput);
  TEST(SYSRUN(cmdstr) == 0);

  fclose(testFilePtr);

}

/* Function Name: testdisplayLights
 * Description:   Runs a series of tests on displayLights.
 */
void testdisplayLights() {

  /* Test 1 */
  unsigned int lightBank1[] = {0x0, 0x0};
  char* expected1 = "---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----";
  runTest(lightBank1, expected1, "Test: 0x0, 0x0");

 /* Test 2 */
  unsigned int lightBank2[] = {0x11111111, 0x88888888};
  char* expected2 = "---* ---* ---* ---* ---* ---* ---* ---* *--- *--- *--- *--- *--- *--- *--- *---";
  runTest(lightBank2, expected2, "Test: 0x11111111, 0x88888888");

  /* Test 3 */
  unsigned int lightBank3[] = {0xFFFFFFFF, 0xFFFFFFFF};
  char* expected3 = "**** **** **** **** **** **** **** **** **** **** **** **** **** **** **** ****";
  runTest(lightBank3, expected3, "Test: 0xFFFFFFFF, 0xFFFFFFFF");

  /* Test 4 */
  unsigned int lightBank4[] = {0x01234567, 0x89ABCDEF};
  char* expected4 = "---- ---* --*- --** -*-- -*-* -**- -*** *--- *--* *-*- *-** **-- **-* ***- ****";
  runTest(lightBank4, expected4, "Test: 0x01234567, 0x89ABCDEF");

  /* Test 5 */
  unsigned int lightBank5[] = {0xDEADBEEF, 0x1337CA75};
  char* expected5 = "**-* ***- *-*- **-* *-** ***- ***- **** ---* --** --** -*** **-- *-*- -*** -*-*";
  runTest(lightBank5, expected5, "Test: 0xDEADBEEF, 0x1337CA75");

}

int main( void ) {
  fprintf(stderr, "Running tests for displayLights...\n");
  testdisplayLights();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
