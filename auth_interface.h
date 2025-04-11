#ifndef AUTH_INTERFACE_H
#define AUTH_INTERFACE_H

#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char routing_number[256];
    unsigned long account_number;
    unsigned char public_key[65];
    unsigned char private_key[32];
    size_t public_key_len;
    size_t private_key_len;
    char error[512];
    bool success;
} ExportedCredentials;

ExportedCredentials createNewUser(const char* password, const char* pin, const char* routingNumber);
ExportedCredentials verifyReturningUser(const char* password, const char* pin, const char* routingNumber, const char* inputAccountNumber);

#ifdef __cplusplus
}
#endif

#endif // AUTH_INTERFACE_H 