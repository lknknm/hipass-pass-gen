#ifndef GENERATOR_H
#define GENERATOR_H


// Generator definition to generate random sequence of characters
// A-Z, a-z, symbols and numbers included.
extern void generate_random_complete(char *password, int characters);
extern void generate_random_CLI(bool AZ_upper, 
                                bool az_lower, 
                                bool numeric,
                                bool symbol,
                                char *password, 
                                int characters);



#endif // GENERATOR_H