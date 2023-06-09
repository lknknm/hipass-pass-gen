#ifndef GENERATOR_H
#define GENERATOR_H


// Generator definition to generate random sequence of characters
// A-Z, a-z, symbols and numbers included.
extern int generate_random_complete(void);
extern int generate_random_CLI(bool CH_TYPE[], char *sufix);
extern void generate_passphrase(void);
#endif // GENERATOR_H