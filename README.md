### Hipass Password Generator

Hipass is a CLI (Command Line Interface) Password Generator that generates random, strong passwords. 
The intent of the project is to generate passwords in a fast, concise way and copy them directly into the clipboard, without having 
to rely on internet services.

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