#ifndef GRAMMAIRE_SIMP_H
#define GRAMMAIRE_SIMP_H

#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"
#include "api.h"

//Contient toutes le fonctions decrivant la grammaire :
//Une fonction par element

//absolute-path = 1* ( "/" segment )
int verifAbsolute_path(char* valeur, Noeud* pere);

// ALPHA = %x41-5A / %x61-7A   ; A-Z / a-z
int verifALPHA(char* valeur, Noeud* pere);

//CRLF = %x0D %x0A
int verifCRLF(char* valeur, Noeud* pere);

// DIGIT = %x30-39  ; 0-9
int verifDIGIT(char* valeur, Noeud* pere);

//HEXDIG  =  DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
int verifHEXDIG(char* valeur, Noeud* pere);

//Htab = %x09
int verifHTAB(char* valeur, Noeud* pere);

//HTTP-message = start-line * ( header-field CRLF ) CRLF [ message-body ]
int verifHTTP_message(char* valeur, Noeud* pere);

//HTTP-name = %x48.54.54.50
int verifHTTP_name(char* valeur, Noeud* pere);

//HTTP-version = HTTP-name "/" DIGIT "." DIGIT
int verifHTTP_version(char* valeur, Noeud* pere);

//method = token
int verifMethod(char* valeur, Noeud* pere);

// obs-text = %x80-FF
int verifObs_text(char* valeur, Noeud* pere);

//origin-form = absolute-path [ "?" query ]
int verifOrigin_form(char* valeur, Noeud* pere);

//pchar = unreserved / pct-encoded / sub-delims / ":" / "@"
int verifPchar(char* valeur, Noeud* pere);

//pct-encoded = "%" HEXDIG HEXDIG
int verifPct_encoded(char* valeur, Noeud* pere);

//query = * ( pchar / "/" / "?" )
int verifQuery(char* valeur, Noeud* pere);

//reason-phrase = * ( HTAB / SP / VCHAR / obs-text )
int verifReason_phrase(char* valeur, Noeud* pere);

//request-line = method SP request-target SP HTTP-version CRLF
int verifRequest_line(char* valeur, Noeud* pere);

//request-target = origin-form
int verifRequest_target(char* valeur, Noeud* pere);

//segment = * pchar
int verifSegment(char* valeur, Noeud* pere);

//SP =  %x20
int verifSP(char* valeur, Noeud* pere);

//sub-delims = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="
int verifSub_delims(char* valeur, Noeud* pere);

//start-line = request-line / status-line
int verifStart_line(char* valeur, Noeud* pere);

//status-code = 3 DIGIT
int verifStatus_code(char* valeur, Noeud* pere);

//status-line = HTTP-version SP status-code SP reason-phrase CRLF
int verifStatus_line(char* valeur, Noeud* pere);

//tchar = "!" / "#" / "$" / "%" / "&" / "'" / "*" / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~" / DIGIT / ALPHA
int verifTchar(char* valeur, Noeud* pere);

//token = 1* tchar
int verifToken(char* valeur, Noeud* pere);

//unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"
int verifUnreserved(char* valeur, Noeud* pere);

//VCHAR = %x21-7E
int verifVCHAR(char* valeur, Noeud* pere);





//
int verif(char* valeur, Noeud* pere);

//
int verif(char* valeur, Noeud* pere);

//
int verif(char* valeur, Noeud* pere);

//
int verif(char* valeur, Noeud* pere);

//
int verif(char* valeur, Noeud* pere);

//
int verif(char* valeur, Noeud* pere);

//
int verif(char* valeur, Noeud* pere);

//
int verif(char* valeur, Noeud* pere);

//
int verif(char* valeur, Noeud* pere);

//
int verif(char* valeur, Noeud* pere);

//
int verif(char* valeur, Noeud* pere);


#endif
