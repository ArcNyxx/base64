#include <stdio.h>
#include "base64.h"

int main(int argc, char *argv[]) {
    char *string = "NXBUwl^MYZVJi47a1*n22@iTCD-%Z3rM&YJoLU&9Ss6Y_T5*sW?ufI27iKN"
    "4Lst%@sA2N7&IX9dXl-D&^-A-B$7=i9dDNdg7ygcK#KBFT?A9T&h|k#=l=3699Rp1pPhJO+fx="
    "fdD^b0s%$i?EPBq$mqX9n3xr*OEMk3*!dbHu=Uy5nc3O9U3h4rCW&lk$EkZ!@XD6*d0Bj#==qbC"
    "nW*g=E0r^ItOIizy0SdMe32xh9xupKZsRwx7hj-YG!Wpc$d^";
    
    char *encode = EncodeBase64(string);
    printf("Encoded:\n%s\n", encode);

    char verify = VerifyBase64(encode);
    printf("Verified:\n%s\n", verify ? "True" : "False");

    char *decode = DecodeBase64(encode);
    printf("Decoded:\n%s\n", decode);
    printf("Original:\n%s\n", string);
    printf("Correct:\n%s\n", strcmp(string, decode) ? "No" : "Yes");
}
