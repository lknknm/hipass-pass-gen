## Hipass Password Generator

Hipass is a CLI (Command Line Interface) Password Generator that generates random, strong passwords. 
The intent of the project is to generate passwords in a fast, concise way and copy them directly into the clipboard, without having 
to rely on internet services.

| CS50x Final Project. This is still under development.  |
|--------------------------------------------------------|

#### Why use a password generator?
Passwords must be strong and unique to each service you're using. This way, attackers will have a harder time guessing your passwords, or even 
<a href="https://www.fortinet.com/resources/cyberglossary/brute-force-attack">"brute forcing"</a> 
the services you can potentially have an account. By having strong and random passwords, it is less likely that an attacker can try combinations with information
they have about you, such as birth date, names of your family members or even the name of your dog. 

That's why password generators comes in handy. They can create strong, unique, random passwords each time they're prompted. 
They can output uppercase A-Z, lowercase a-z, special characters and numbers to be as random as possible so they are difficult for an attacker to remember,
as well as extremely difficult to brute force.

Since, according to NIST (as cited by Gary Orenstein, from Bitwarden) the 
<a href="https://bitwarden.com/blog/how-long-should-my-password-be/">
"Password length has been found to be a primary factor in characterizing password strength"
</a>
I've capped the minimum value of generating a password with a minimum of 14 characters length. 
With that, it's possible to generate password that would take at least a century to crack. 

#### Where should I store my passwords, then?
Password managers, period. Also, it's recommended that you keep a very strong password for that too, with a separate e-mail to login.
Usually a 2FA is also recommended for "further improvement on security", but for a password manager this is pratically mandatory for obvious reasons. 
You can use offline or online solutions for that. My top 3 recommendations are: 
<a href="https://bitwarden.com/">BitWarden</a>, <a href="https://usa.kaspersky.com/about/company">Kaspersky</a> and <a href="https://www.lastpass.com/pt">LastPass</a>. 
Of course they also offer robust password generators, but if you want an offline, fast solution, you can recursively use 
<a href="https://github.com/lknknm/hipass-pass-gen">Hipass</a>.

### Documentation
- To see how to build the project, please take a look at the developer documentation and follow the [Build Manual](./doc/dev/BUILD.md). 
- To see how we style our code, please refer to the [Code Style Guide](./doc/dev/STYLEGUIDE.md)

### Usage (to be implemented)
```
  ./hipass [--flag] [f]
```

```
  *no flags*        User will be prompted to choose character length of a random password with 
                    A-Z uppercase, a-z lowercase, numbers and special characters

The following arguments will generate passwords with the ones user had selected.
Example: ./hipass AZ num sym az

  AZ                Include A to Z uppercase characters
  az                Include a to z lowercase characters
  sym               Include special symbols (!@#^&*$)
  num               Include digits from 0 to 9

The following arguments can be passed as flags:  

  --h --help        Print out help text
  --v --version     Print version
  --update          Update to latest release
       
  --prefix PREFIX   Generate password with a desired prefix
  --sufix SUFIX     Generate password with a desired sufix
       
  --passphrase      Generate passphrase with the following flags
         -sep%      Separate words with "%"
```

### Generating random characters
Generating random characters and random numbers based on a seed of time such as `srand(time(NULL))` and `rand()` may lead to several password exploits. A simple example of this is that seeding a `random` generator with `time(NULL)` and calling `generate_password` twice in `main()` will generate the same password twice. This means that seeding with `time(NULL)` will not generate milisecond time and will not use any kernel processes of the user's computer (adding solely GETPID in the equation won't help much either). 

For this reason, this password generator is using [this set of functions written](https://github.com/jleffler/soq/tree/6118083dc6af1daa0a0f0f54d6414f2f6c0e9049/src/so-7594-6155) by [Jonathan Leffler](https://github.com/jleffler). His random seed generation uses the widespread `/dev/random` and `/dev/urandom` devices as a [cryptographically secure pseudorandom number generator](https://en.wikipedia.org/wiki/Cryptographically_secure_pseudorandom_number_generator).

>"The random seed code generation code in `randseed.c` and `randseed.h` uses `/dev/random` by default but can be configured to use a number of other algorithms. The files `crc.c` and `crc.h` contain some CRC algorithms if your system has neither `/dev/random` (nor `/dev/urandom`) nor `arc4random()`.
>
>The random number generation code using POSIX nrand48() is in prng48.c and prng48.h. You should call prng48_seed() with an array of 3 unsigned short integers that represent the random seed - though there is a default value. You then call prng48_rand() with the lower and upper bounds of the range of 31-bit unsigned integers that you want. The algorithm takes care to ensure that there is no bias in the result.
>
>The files kludge.c, kludge.h, posixver.h, stderr.c, and stderr.h can be found in the src/libsoq sub-directory. They are needed for the FEATURE macro used in randseed.c and testing, etc."

>Leffler, Jonathan, Stack Overflow Question 75494-6155, (2023), GitHub repository, https://github.com/jleffler/soq/tree/6118083dc6af1daa0a0f0f54d6414f2f6c0e9049/src/so-7594-6155

### License
This project uses GNU GENERAL PUBLIC LICENSE 3.0.