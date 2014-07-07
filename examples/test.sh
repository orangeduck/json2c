json2c -c colors.json
json2c -c customer.json
json2c facebook.json
json2c flickr.json
json2c -c glossary.json
json2c -c interop.json
json2c -c maps.json
json2c menu.json
json2c poems.json
json2c product.json
json2c scores.json
json2c twitter.json
json2c viewer.json --no-array-count-uppercase --no-guard-uppercase
json2c -c webapp.json
json2c -c widget.json
json2c -c youtube.json
gcc -std=c99 -c colors.c
gcc -std=c99 -c customer.c
gcc -std=c99 -c facebook.c
gcc -std=c99 -c flickr.c
gcc -std=c99 -c glossary.c
gcc -std=c99 -c interop.c
gcc -std=c99 -c maps.c
gcc -std=c99 -c menu.c
gcc -std=c99 -c poems.c
gcc -std=c99 -c product.c
gcc -std=c99 -c scores.c
gcc -std=c99 -c twitter.c
gcc -std=c99 -c viewer.c
gcc -std=c99 -c webapp.c
gcc -std=c99 -c widget.c
gcc -std=c99 -c youtube.c
rm *.o