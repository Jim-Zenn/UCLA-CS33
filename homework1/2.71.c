/*
 * You just started working for a company that is implementing a set of
 * procedures to operate on a data structure where 4 signed bytes are packed
 * into a 32-bit unsigned. Bytes within the word are numbered from 0 (least
 * signiﬁcant) to 3 (most signiﬁcant). You have been assigned the task of
 * implementing a function for a machine using two’s-complement arithmetic and
 * arithmetic right shifts with the following prototype:
 *
 * // Declaration of data type where 4 bytes are packed into an unsigned
 * typedef unsigned packed_t;
 *
 * // Extract byte from word. Return as signed integer
 * int xbyte(packed_t word, int bytenum);
 *
 * That is, the function will extract the designated byte and sign extend it to
 * be a 32-bit int.
 *
 * Your predecessor (who was ﬁred for incompetence) wrote the following code:
 *
 * // Failed attempt at xbyte
 *
 * int xbyte(packed_t word, int bytenum) {
 *   return (word >> (bytenum << 3)) & 0xFF;
 * }
 *
 */

// A. What is wrong with this code?
//    It performs unsigned extend instead of signed extend on the chosen byte.

// B. Give a correct implementation of the function that uses only left and
//    right shifts, along with one subtraction.


// unsigned alone is unsigned int, hence 4 bytes
typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum) {
  return word << ((3 - bytenum) << 3) >> 24;
}
