+++
date = "2015-05-05T18:59:17-05:00"
title = "Using GPG"
showonlyimage = false
image = "/projects/GPG/Public_key_encryption.svg"
draft = false

+++

A summary of using the command line tool GnuPG for secure communication.
<!--more-->

There is a great deal of info out there about PGP and GPG but I could never find what I wanted summarized nicely in one place. This is my attempt to do that.

#### PROCESS OUTLINE 

* **Create PGP public/private key pair.**
* **Backup public key, private key, and emergency private key revocation certificate in a SECURE location.**
* **Upload public key to keyserver** (e.g. pgp.mit.edu)\\
(Keyservers share keys between each other so it
is only necessary to upload to one server.)
* **Download the public keys you wish to sign.**
Signing is a confirmation that a public key (user ID/email) belongs to the person it claims to belong to and that you believe that the private key associated with that public key is safely kept by that person. THIS IS NOT SOMETHING TO BE DONE LIGHTLY. THIS IS HOW A WEB OF TRUST IS BUILT.
* **CONFIRM THE KEY FINGERPRINT IN A SECURE WAY** (e.g. in person)
* **Sign the user IDs that you trust, you can sign any subset of a user's IDs.** (Many IDs (emails, images) can be associated with one public key.)
* **Upload the keys you've signed back to the keyserver.**\\
Optional: You can also 'trust' a key/ID. Signing a key is a assertion of the validity of the key, that is, the person  with the associated private key is who they claim to be. Trusting a key is local only (trust values don't get uploaded to a keyserver) and is an assertion of how much you believe you can trust other keys signed by that person. GPG will by default trust a key if it is signed by a key you 'fully' trust or by three keys you 'partially' trust. Only 'ultimately' trust yourself.
* **Test sending and receiving messages**

Note these commands work on Mac and Linux with both gpg and gpg2 (as far as I am aware).


#### CREATING A PGP KEY 

`gpg2 --gen-key`

* Use 4096 RSA (1)
* Expiration date (less than 2 years is recommended, this date can be extended later and acts as a dead man switch)
* Enter (real) full name
* Enter real email address (advisable to use dedicated)
* Enter optional comment (shown along with key name to others)
* Enter a passphrase (length at least 12, memorable)(Can be changed)
  - A long passphrase of over 6 words from more than one language will be very resistant to brute force and dictionary attacks but can be made easy to type and remember.

#### BACKUP YOUR PRIVATE AND PUBLIC KEY

Export public key

`gpg2 --export -a "User Name" > user.pub.key`

Export private key

`gpg2 --export-secret-key -a "User Name" > user.priv.key`

Create emergency revocation certificate. This is the ONLY way to revoke your public key if you lose access to your private key.

`gpg2 --output user.rev.asc --gen-revoke key_user_name`

**BACK THESE FILES UP IN A SECURE LOCATION (SUCH AS CD/PAPER IN A BANK VAULT, ENCRYPTED DRIVE, ETC...)**


#### MANAGE AND EDIT KEYS 


List available public keys

`gpg2 --list-keys`

List available private keys

`gpg2 --list-secret-keys`

Display fingerprint of all public keys (Can be combined with `--list-secret-keys`)

`gpg2 --fingerprint`

Edit a key

`gpg2 --edit-key key_user_name/email`

Type "help" to see list of commands in edit mode


#### EXCHANGING, SIGNING AND TRUSTING KEYS


###### Upload public key to keyserver

*This can NEVER be deleted, only revoked, so don't clutter the server.*

`gpg2 --keyserver pgp.mit.edu --send-keys KEY_ID`

###### Download public key from keyserver 

`gpg2 --keyserver pgp.mit.edu --recv-keys KEY_ID`

###### Sign/validate user ID (AKA public key signing)

`gpg2 --sign-key key_user_name/email`

Will ask to confirm which user IDs to sign. You can sign specific or all user IDs.

###### Trusting keys

`gpg2 --edit-key key_user_name/email`

`gpg2> trust`

Default is "I don't know."
Level of trust is how much you trust both their understanding of PGP (so they won't make a mistake) and how much you trust their commitment to properly validating keys. "Ultimate" is a special level reserved for your own key.


#### SENDING AND RECEIVING 

###### Decrypt file

`gpg2 -d <file_name>` (Spits out text to the terminal.)

`gpg2 -d <file_name> > file.txt` (Saves text to file.)

###### Encrypt file (minimal example)

`gpg2 --encrypt -r "recipient_name" <file_name>`

###### Encrypt, sign, specify output name

Use -a to export an ASCII file (for copying into a text field and such)

`gpg2 -es -o <output_filename> -r "Recipient" <file_name>`

###### Clearsign 

Encrypts with your private key so only your public key can be used
to decrypt it (proves it comes from you and that the data hasn't been tampered with).

`gpg2 --clearsign <file_name>`

Use -u <user_name> to specify a non-default private key

Note that the keys/IDs of the sender and recipient can be seen by a third party even if they can't decrypt the message. The flag below can hid the recipient. See the examples section for more discussion.

###### To hide the intended recipient from a third-party

`gpg2 --hidden-recipient -e -r "recipient_name" <file_name>`

#### EXAMPLE 

Recently I was playing on online game of Diplomacy (a strategy game like Risk) with friends and we decided to add a crypto element. Below I'll go through how we communicated using pgp. Of course you don't have to use gpg or the terminal to do this, but it does give you a better sense of what is going on behind the scenes. We started off by each creating a private/public key pair for the country we were playing as. We didn't want to clutter key servers so all keys were shared via text on a simple message board my friend programmed on his server.

##### Sharing public key

Export public key

`gpg2 --export -a "User Name" > user.pub.key`

Make a plain text file with your intro message and sign that file (only need -u option if you have a different default key)

`gpg2 -u "yourCountry" --clearsign message.txt`

This will output a file `message.txt.asc` which will have the message in clear text and a crypto signature proving the key which was used to sign it

Copy the contents of the `message.txt.asc` file into a message on the board, and then also copy the contents of the `user.pub.key` and append to the same message.

##### Proving your identity

The easiest way is to generate a key fingerprint and put that in a message on the vDiplomacy site so we know for sure which key belongs to which country.

`gpg2 --fingerprint`

Outputs something like this:
```
pub   1024R/DB9C59CF 2015-01-13
      Key fingerprint = E03D 7518 B11E BE5C 82BE 2143 FB43 9F02 DB9C 59CF
uid       [ultimate] Austria 
sub   1024R/5CD5DF64 2015-01-13
```

Copy that key fingerprint into the vDip message board.

##### Checking someone's identity 

First import their public key. Make a file named country_name.pub.key and copy the key into it (Including the "BEGIN" and "END" lines)

`gpg2 --import country_name.pub.key`

Now check the fingerprint

`gpg2 --fingerprint`

Lists all keys on your keyring, look for the one you just imported and check the fingerprint against that on the vDip message board.

Check the signature of the message

Copy from the "BEGIN SIGNED MESSAGE" line to the "END SIGNATURE" line into a plain text file: `file_name.txt.asc`

`gpg2 -d file_name.txt.asc`

You should see an output like this:
```
gpg: Signature made Tue 13 Jan 2015 12:45:02 PM CST using RSA key ID xxxxxxxx                                                         
gpg: Good signature from "user_name" 
```

##### Communicating

To send a signed, encrypted message to a single person, create a plain text file as before with the contents of your message save as something like `otherCountry_msg1.txt`

`gpg2 -eas -u "yourCountry" -o otherCountry_msg1.asc -r "otherCountry" otherCountry_msg1.txt`

Copy the contents of the newly created file `otherCountry_msg1.asc` into a message on the board. You can make a note at the top who it is for, or just let everyone try to decrypt it.

To decrypt a message, copy the contents from the BEGIN to END lines into a text file named something like `otherCountry_msg2.asc`

`gpg2 -d otherCountry_msg2.asc > otherCountry_msg2.txt`

Note that if the command above is used, a third party can see who is talking, even if they can't read the message. For example, a message between Russia and England when tried to be decrypted by Austria gave the following:

```
gpg2 -d temp.enc
gpg: encrypted with 1024-bit RSA key, ID D6762868, created 2015-01-15
      "Russia"
gpg: encrypted with 4096-bit RSA key, ID 7D5EF8AB, created 2015-01-12
      "England Anonymous"
gpg: decryption failed: No secret key
```

This can be partially remedied by the use of the `--hidden-recipient` flag, but there doesn't seem to be a way to hide the sender. Of course the third party would have to have the sender's and recipient's public keys for this to work. It also seems to depend some on the software being used, I haven't quite figured out exactly how.
