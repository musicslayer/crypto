#ifndef _SECP256K1_ECDH_
# define _SECP256K1_ECDH_

# include "secp256k1.h"

# ifdef __cplusplus
extern "C" {
# endif

/** A pointer to a function that applies hash function to a point
 *
 *  Returns: 1 if a point was successfully hashed. 0 will cause ecdh to fail
 *  Out:    output:     pointer to an array to be filled by the function
 *  In:     x:          pointer to a 32-byte x coordinate
 *          y:          pointer to a 32-byte y coordinate
 *          data:       Arbitrary data pointer that is passed through
 */
typedef int (*secp256k1_ecdh_hash_function)(
  unsigned char *output,
  const unsigned char *x,
  const unsigned char *y,
  void *data
);

/** An implementation of SHA256 hash function that applies to compressed public key. */
SECP256K1_API extern const secp256k1_ecdh_hash_function secp256k1_ecdh_hash_function_sha256;

/** A default ecdh hash function (currently equal to secp256k1_ecdh_hash_function_sha256). */
SECP256K1_API extern const secp256k1_ecdh_hash_function secp256k1_ecdh_hash_function_default;

/** Compute an EC Diffie-Hellman secret in constant time
 *  Returns: 1: exponentiation was successful
 *           0: scalar was invalid (zero or overflow)
 *  Args:    ctx:        pointer to a context object (cannot be NULL)
 *  Out:     result:     a 32-byte array which will be populated by an ECDH
 *                       secret computed from the point and scalar
 *  In:      pubkey:     a pointer to a secp256k1_pubkey containing an
 *                       initialized public key
 *           privkey:    a 32-byte scalar with which to multiply the point
 */
SECP256K1_API SECP256K1_WARN_UNUSED_RESULT int secp256k1_ecdh(
  const secp256k1_context* ctx,
  unsigned char *result,
  const secp256k1_pubkey *pubkey,
  const unsigned char *privkey
) SECP256K1_ARG_NONNULL(1) SECP256K1_ARG_NONNULL(2) SECP256K1_ARG_NONNULL(3) SECP256K1_ARG_NONNULL(4);

SECP256K1_API SECP256K1_WARN_UNUSED_RESULT int secp256k1_ecdh_arg6(
  const secp256k1_context* ctx,
  unsigned char *output,
  const secp256k1_pubkey *pubkey,
  const unsigned char *privkey,
  secp256k1_ecdh_hash_function hashfp,
  void *data
) SECP256K1_ARG_NONNULL(1) SECP256K1_ARG_NONNULL(2) SECP256K1_ARG_NONNULL(3) SECP256K1_ARG_NONNULL(4);

# ifdef __cplusplus
}
# endif

#endif
