#ifndef __ANNEXE_H__
#define __ANNEXE_H__

#define DIR_DATA "./dataHttpServer"
#define START_PHP_FILENAME "proxy:fcgi://127.0.0.1:9000//home/leovalette/Documents/php"
#define ERROR_400 "HTTP/1.1 400 Bad Request\r\n\r\n"
#define ERROR_404 "HTTP/1.1 404 Not Found\r\n\r\n"
#define ERROR_505 "HTTP/1.1 505 HTTP Version Not Supported\r\n\r\n"
#define ERROR_501 "HTTP/1.1 501 Not Implemented\r\n\r\n"
#define ERROR_500 "HTTP/1.1 500 Internal Server Error\r\n\r\n"
#define ERROR_405 "HTTP/1.1 405 Method Not Allowed\r\n"
#define REPONSE_STATUS "HTTP/1.1 200 OK\r\n"
#define REPONSE_CONTENT_TYPE "Content-Type: "
#define REPONSE_CONTENT_LENGTH "Content-Length: "
#define REPONSE_ALLOW "Allow: "
#define REPONSE_DATE "Date: "
#define SAUT_DE_LIGNE "\r\n"
#define MAX_SIZE 1000
#define SIZE_MIME 31
#define PETITE_JOKE "C est pas nous, c'est le php qui bug\r\n\r\n"

#define HTTP1_1 1000
#define HTTP1_0 1001
#define GET_METHODE 1002
#define HEAD_METHODE 1003
#define HEADER_TYPE 1004
#define HEADER_LENGTH 1005
#define NO_HEADER 1006
#define CLOSE 1007
#define KEEP_ALIVE 1008
#define WRONG_SYNTAX 1009
#define POST_METHODE 1010

#define ERROR_PHP 1011

#endif
