# Game Authors
game authors are ordered by first contribution:
* **Ryan McClue**([@`'M4_GITHUB_USER_NAME_M4`'](https://github.com/OutbackMan))
- GPG key: `'M4_GPG_KEY_M4`'

// gpg implements pgp

// git tag -s -m "e" && git push --tags (-s will use gpg key from email, -u allows this to be specified)

// signing verifies data has not changed (sha1sum is not enough as website could be hacked, and gives no info on user or date) 

// sign data with my private key (gpg --list-secret-keys; gpg --sign file.txt). 
// then have to extract encapsulated data from generated .gpg file
// instead, do (gpg --detach-sign file.txt)

// anyone with my public key can verify it was me. gpg --import pubkey.asc
// gpg --fingerprint 4FA123 (fingerprint is a series of bytes used to identify a longer public key)
// (gpg --verify) (assumes related data in same directory)

