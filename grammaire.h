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

//Connection = * ( "," OWS ) connection-option * ( OWS "," [ OWS connection-option ] )
int verifConnection(char* valeur, Noeud* pere);

//Connection-header = "Connection" ":" OWS Connection OWS
int verifConnection_header(char* valeur, Noeud* pere);

//connection-option = token
int verifConnection_option(char* valeur, Noeud* pere);

//Content-Length = 1* DIGIT
int verifContent_length(char* valeur, Noeud* pere);

//Content-Length-header = "Content-Length" ":" OWS Content-Length OWS
int verifContent_length_header(char* valeur, Noeud* pere);

//Content-Type = media-type
int verifContent_Type(char* valeur, Noeud* pere);

//Content-Type-header = "Content-Type" ":" OWS Content-Type OWS
int verifContent_type_header(char* valeur, Noeud* pere);

//Cookie-header = "Cookie:" OWS cookie-string OWS
int verifCookie_header(char* valeur, Noeud* pere);

//cookie-name = token
int veriCookie_name(char* valeur, Noeud* pere);

//cookie-octet = %x21 / %x23-2B / %x2D-3A / %x3C-5B / %x5D-7E
int verifCookie_octet(char* valeur, Noeud* pere);

//cookie-pair = cookie-name "=" cookie-value
int verifCookie_pair(char* valeur, Noeud* pere);

//cookie-string = cookie-pair * ( ";" SP cookie-pair )
int verifCookie_string(char* valeur, Noeud* pere);

//cookie-value = ( DQUOTE * cookie-octet DQUOTE ) / * cookie-octet
int verifCookie_value(char* valeur, Noeud* pere);

//CRLF = %x0D %x0A
int verifCRLF(char* valeur, Noeud* pere);

// DIGIT = %x30-39  ; 0-9
int verifDIGIT(char* valeur, Noeud* pere);

//DQUOTE%x22
int verifDQUOTE(char* valeur, Noeud* pere);

/*header-field = Connection-header / Content-Length-header / Content-Type-header / Cookie-header / Transfer-Encoding-header
/ Expect-header / Host-header / ( field-name ":" OWS field-value OWS )*/
int verifHeader_field(char* valeur, Noeud* pere);

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

//media-type = type "/" subtype * ( OWS ";" OWS parameter )
int verifMedia_type(char* valeur, Noeud* pere);

//method = token
int verifMethod(char* valeur, Noeud* pere);

// obs-text = %x80-FF
int verifObs_text(char* valeur, Noeud* pere);

//origin-form = absolute-path [ "?" query ]
int verifOrigin_form(char* valeur, Noeud* pere);

//OWS = * ( SP / HTAB )
int verifOWS(char* valeur, Noeud* pere);

//parameter = token "=" ( token / quoted-string )
int verifParameter(char* valeur, Noeud* pere);

//pchar = unreserved / pct-encoded / sub-delims / ":" / "@"
int verifPchar(char* valeur, Noeud* pere);

//pct-encoded = "%" HEXDIG HEXDIG
int verifPct_encoded(char* valeur, Noeud* pere);

//qdtext = HTAB / SP / "!" / %x23-5B / %x5D-7E / obs-text
int verifQdtext(char* valeur, Noeud* pere);

//query = * ( pchar / "/" / "?" )
int verifQuery(char* valeur, Noeud* pere);

//quoted-pair = "\" ( HTAB / SP / VCHAR / obs-text )
int verifQuoted_Pair(char* valeur, Noeud* pere);

//quoted-string = DQUOTE * ( qdtext / quoted-pair ) DQUOTE
int verifQuoted_string(char* valeur, Noeud* pere);

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

//subtype = token
int verifSubtype(char* valeur, Noeud* pere);

//tchar = "!" / "#" / "$" / "%" / "&" / "'" / "*" / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~" / DIGIT / ALPHA
int verifTchar(char* valeur, Noeud* pere);

//token = 1* tchar
int verifToken(char* valeur, Noeud* pere);

//type = token
int verifType(char* valeur, Noeud* pere);

//unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"
int verifUnreserved(char* valeur, Noeud* pere);

//VCHAR = %x21-7E
int verifVCHAR(char* valeur, Noeud* pere);

//je me suis arrété a HTML-message>header-field>Cookie-header


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
