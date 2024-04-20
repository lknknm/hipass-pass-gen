#ifndef GENERATOR_H
#define GENERATOR_H


// Generator definition to generate random sequence of characters
// A-Z, a-z, symbols and numbers included.
extern int generate_random_CLI(bool CH_TYPE[], char *sufix, char *prefix);
extern void generate_passphrase(char separator);
#endif // GENERATOR_H