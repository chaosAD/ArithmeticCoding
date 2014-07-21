#include "unity.h"
#include "Arithmetic.h"

void setUp(void) {}

void tearDown(void) {}

void test_streamWriteBit_1_0_1_should_store_1_0_1_in_buffer() {
  char buffer[10] = {0xff};
  Stream out = {.buffer=buffer, .length=10, .byteIndex=0, .bitIndex=0};
  TEST_ASSERT_EQUAL(1, streamWriteBit(&out, 1));
  TEST_ASSERT_EQUAL(0, out.byteIndex);
  TEST_ASSERT_EQUAL(1, out.bitIndex);
  TEST_ASSERT_EQUAL_HEX8(1, out.buffer[0]);
  
  TEST_ASSERT_EQUAL(2, streamWriteBit(&out, 0));
  TEST_ASSERT_EQUAL(0, out.byteIndex);
  TEST_ASSERT_EQUAL(2, out.bitIndex);
  TEST_ASSERT_EQUAL_HEX8(1, out.buffer[0]);

  TEST_ASSERT_EQUAL(3, streamWriteBit(&out, 1));
  TEST_ASSERT_EQUAL(0, out.byteIndex);
  TEST_ASSERT_EQUAL(3, out.bitIndex);
  TEST_ASSERT_EQUAL_HEX8(5, out.buffer[0]);
}

void test_streamWriteBit_given_bitIndex_is_7_and_1_0_1_should_store_0x80_in_buffer0_and_0x02_in_buffer1() {
  char buffer[10] = {0, 0xff};
  Stream out = {.buffer=buffer, .length=10, .byteIndex=0, .bitIndex=7};
  TEST_ASSERT_EQUAL(8, streamWriteBit(&out, 1));
  TEST_ASSERT_EQUAL(1, out.byteIndex);
  TEST_ASSERT_EQUAL(0, out.bitIndex);
  TEST_ASSERT_EQUAL_HEX8(0x80, out.buffer[0]);
  TEST_ASSERT_EQUAL_HEX8(0xff, out.buffer[1]);
  
  TEST_ASSERT_EQUAL(9, streamWriteBit(&out, 0));
  TEST_ASSERT_EQUAL(1, out.byteIndex);
  TEST_ASSERT_EQUAL(1, out.bitIndex);
  TEST_ASSERT_EQUAL_HEX8(0x80, out.buffer[0]);
  TEST_ASSERT_EQUAL_HEX8(0x0, out.buffer[1]);

  TEST_ASSERT_EQUAL(10, streamWriteBit(&out, 1));
  TEST_ASSERT_EQUAL(1, out.byteIndex);
  TEST_ASSERT_EQUAL(2, out.bitIndex);
  TEST_ASSERT_EQUAL_HEX8(0x80, out.buffer[0]);
  TEST_ASSERT_EQUAL_HEX8(0x02, out.buffer[1]);
}

void test_getRangeOfSymbol_given_3_symbols_should_return_the_middle_pdf(void) {
	Range range;
	PDFEntry pdfTable[] = {
		{1, 10},
		{2, 20},
		{3, 50}
	};	
	TEST_ASSERT_EQUAL(1, getRangeOfSymbol(&range, 2, pdfTable, 3));
  TEST_ASSERT_EQUAL_INT32(MAX_RANGE*10/(10+20+50), range.lower);
  TEST_ASSERT_EQUAL_INT32(MAX_RANGE*(10+20)/(10+20+50) - 1, range.upper);
}

void test_getRangeOfSymbol_given_3_symbols_and_unavailable_symbol_should_return_0(void) {
	Range range;
	PDFEntry pdfTable[] = {
		{1, 10},
		{2, 20},
		{3, 50}
	};	
	TEST_ASSERT_EQUAL(0, getRangeOfSymbol(&range, 0, pdfTable, 3));
}
