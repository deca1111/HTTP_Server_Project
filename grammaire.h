#ifndef GRAMMAIRE_SIMP_H
#define GRAMMAIRE_SIMP_H

#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"
#include "api.h"

//Contient toutes le fonctions decrivant la grammaire :
//Une fonction par element

//absolute-path = 1* ( "/" segment )
int verifAbsolute_path(char* valeur, Noeud* pere, int index, int long_max);

// ALPHA = %x41-5A / %x61-7A   ; A-Z / a-z
int verifALPHA(char* valeur, Noeud* pere, int index, int long_max);

//BWS = OWS
int verifBWS(char* valeur, Noeud* pere, int index, int long_max);

//Connection = * ( "," OWS ) connection-option * ( OWS "," [ OWS connection-option ] )
int verifConnection(char* valeur, Noeud* pere, int index, int long_max);

//Connection-header = "Connection" ":" OWS Connection OWS
int verifConnection_header(char* valeur, Noeud* pere, int index, int long_max);

//connection-option = token
int verifConnection_option(char* valeur, Noeud* pere, int index, int long_max);

//Content-Length = 1* DIGIT
int verifContent_length(char* valeur, Noeud* pere, int index, int long_max);

//Content-Length-header = "Content-Length" ":" OWS Content-Length OWS
int verifContent_length_header(char* valeur, Noeud* pere, int index, int long_max);

//Content-Type = media-type
int verifContent_Type(char* valeur, Noeud* pere, int index, int long_max);

//Content-Type-header = "Content-Type" ":" OWS Content-Type OWS
int verifContent_type_header(char* valeur, Noeud* pere, int index, int long_max);

//Cookie-header = "Cookie:" OWS cookie-string OWS
int verifCookie_header(char* valeur, Noeud* pere, int index, int long_max);

//cookie-name = token
int veriCookie_name(char* valeur, Noeud* pere, int index, int long_max);

//cookie-octet = %x21 / %x23-2B / %x2D-3A / %x3C-5B / %x5D-7E
int verifCookie_octet(char* valeur, Noeud* pere, int index, int long_max);

//cookie-pair = cookie-name "=" cookie-value
int verifCookie_pair(char* valeur, Noeud* pere, int index, int long_max);

//cookie-string = cookie-pair * ( ";" SP cookie-pair )
int verifCookie_string(char* valeur, Noeud* pere, int index, int long_max);

//cookie-value = ( DQUOTE * cookie-octet DQUOTE ) / * cookie-octet
int verifCookie_value(char* valeur, Noeud* pere, int index, int long_max);

//CRLF = %x0D %x0A
int verifCRLF(char* valeur, Noeud* pere, int index, int long_max);

//dec-octet = "25" %x30-35 / "2" %x30-34 DIGIT / "1" 2 DIGIT / %x31-39 DIGIT / DIGIT
int verifDec_octet(char* valeur, Noeud* pere, int index, int long_max);

// DIGIT = %x30-39  ; 0-9
int verifDIGIT(char* valeur, Noeud* pere, int index, int long_max);

//DQUOTE%x22
int verifDQUOTE(char* valeur, Noeud* pere, int index, int long_max);

//Expect-header = "Expect" ":" OWS Expect OWS
int verifExpect_header(char* valeur, Noeud* pere, int index, int long_max);

//Expect = "100-continue"
int verifExpect(char* valeur, Noeud* pere, int index, int long_max);

//field-content = field-vchar [ 1* ( SP / HTAB ) field-vchar ]
int verifField_content(char* valeur, Noeud* pere, int index, int long_max);

//field-name = token
int verifField_name(char* valeur, Noeud* pere, int index, int long_max);

//field-value = * ( field-content / obs-fold )
int verifField_value(char* valeur, Noeud* pere, int index, int long_max);

//field-vchar = VCHAR / obs-text
int verifFIeld_vchar(char* valeur, Noeud* pere, int index, int long_max);

//h16 = 1*4 HEXDIG
int verifH16(char* valeur, Noeud* pere, int index, int long_max);

/*header-field = Connection-header / Content-Length-header / Content-Type-header / Cookie-header / Transfer-Encoding-header
/ Expect-header / Host-header / ( field-name ":" OWS field-value OWS )*/
int verifHeader_field(char* valeur, Noeud* pere, int index, int long_max);

//HEXDIG  =  DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
int verifHEXDIG(char* valeur, Noeud* pere, int index, int long_max);

//Host-header = "Host" ":" OWS Host OWS
int verifHost_header(char* valeur, Noeud* pere, int index, int long_max);

//Host = uri-host [ ":" port ]
int verifHost_Maj(char* valeur, Noeud* pere, int index, int long_max);

//host = IP-literal / IPv4address / reg-name
int verifHost_Min(char* valeur, Noeud* pere, int index, int long_max);

//Htab = %x09
int verifHTAB(char* valeur, Noeud* pere, int index, int long_max);

//HTTP-message = start-line * ( header-field CRLF ) CRLF [ message-body ]
int verifHTTP_message(char* valeur, Noeud* pere, int index, int long_max);

//HTTP-name = %x48.54.54.50
int verifHTTP_name(char* valeur, Noeud* pere, int index, int long_max);

//HTTP-version = HTTP-name "/" DIGIT "." DIGIT
int verifHTTP_version(char* valeur, Noeud* pere, int index, int long_max);

//IP-literal = "[" ( IPv6address / IPvFuture ) "]"
int verifIP_literal(char* valeur, Noeud* pere, int index, int long_max);

//IPv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet
int verifIPv4address(char* valeur, Noeud* pere, int index, int long_max);

//IPv6address = 6 ( h16 ":" ) ls32 / "::" 5 ( h16 ":" ) ls32 / [ h16 ] "::" 4 ( h16 ":" ) ls32 / [ h16 *1 ( ":" h16 ) ] "::" 3 ( h16 ":" ) ls32 / [ h16 *2 ( ":" h16 ) ] "::" 2 ( h16 ":" ) ls32 / [ h16 *3 ( ":" h16 ) ] "::" h16 ":" ls32 / [ h16 *4 ( ":" h16 ) ] "::" ls32 / [ h16 *5 ( ":" h16 ) ] "::" h16 / [ h16 *6 ( ":" h16 ) ] "::"
int verifIPv6address(char* valeur, Noeud* pere, int index, int long_max);

//IPvFuture = "v" 1* HEXDIG "." 1* ( unreserved / sub-delims / ":" )
int verifIPvFuture(char* valeur, Noeud* pere, int index, int long_max);

//ls32 = ( h16 ":" h16 ) / IPv4address
int verifLs32(char* valeur, Noeud* pere, int index, int long_max);

//media-type = type "/" subtype * ( OWS ";" OWS parameter )
int verifMedia_type(char* valeur, Noeud* pere, int index, int long_max);

//message-body = * OCTET
int verifMessage_body(char* valeur, Noeud* pere, int index, int long_max);

//method = token
int verifMethod(char* valeur, Noeud* pere, int index, int long_max);

//obs-fold = CRLF 1* ( SP / HTAB )
int verifObs_fold(char* valeur, Noeud* pere, int index, int long_max);

// obs-text = %x80-FF
int verifObs_text(char* valeur, Noeud* pere, int index, int long_max);

//OCTET          =  %x00-FF; 8 bits of daa
int verifOCTET(char* valeur, Noeud* pere, int index, int long_max);

//origin-form = absolute-path [ "?" query ]
int verifOrigin_form(char* valeur, Noeud* pere, int index, int long_max);

//OWS = * ( SP / HTAB )
int verifOWS(char* valeur, Noeud* pere, int index, int long_max);

//parameter = token "=" ( token / quoted-string )
int verifParameter(char* valeur, Noeud* pere, int index, int long_max);

//pchar = unreserved / pct-encoded / sub-delims / ":" / "@"
int verifPchar(char* valeur, Noeud* pere, int index, int long_max);

//pct-encoded = "%" HEXDIG HEXDIG
int verifPct_encoded(char* valeur, Noeud* pere, int index, int long_max);

//port = * DIGIT
int verifPort(char* valeur, Noeud* pere, int index, int long_max);

//qdtext = HTAB / SP / "!" / %x23-5B / %x5D-7E / obs-text
int verifQdtext(char* valeur, Noeud* pere, int index, int long_max);

//query = * ( pchar / "/" / "?" )
int verifQuery(char* valeur, Noeud* pere, int index, int long_max);

//quoted-pair = "\" ( HTAB / SP / VCHAR / obs-text )
int verifQuoted_Pair(char* valeur, Noeud* pere, int index, int long_max);

//quoted-string = DQUOTE * ( qdtext / quoted-pair ) DQUOTE
int verifQuoted_string(char* valeur, Noeud* pere, int index, int long_max);

//reason-phrase = * ( HTAB / SP / VCHAR / obs-text )
int verifReason_phrase(char* valeur, Noeud* pere, int index, int long_max);

//request-line = method SP request-target SP HTTP-version CRLF
int verifRequest_line(char* valeur, Noeud* pere, int index, int long_max);

//request-target = origin-form
int verifRequest_target(char* valeur, Noeud* pere, int index, int long_max);

//segment = * pchar
int verifSegment(char* valeur, Noeud* pere, int index, int long_max);

//SP =  %x20
int verifSP(char* valeur, Noeud* pere, int index, int long_max);

//sub-delims = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="
int verifSub_delims(char* valeur, Noeud* pere, int index, int long_max);

//start-line = request-line / status-line
int verifStart_line(char* valeur, Noeud* pere, int index, int long_max);

//status-code = 3 DIGIT
int verifStatus_code(char* valeur, Noeud* pere, int index, int long_max);

//status-line = HTTP-version SP status-code SP reason-phrase CRLF
int verifStatus_line(char* valeur, Noeud* pere, int index, int long_max);

//subtype = token
int verifSubtype(char* valeur, Noeud* pere, int index, int long_max);

//tchar = "!" / "#" / "$" / "%" / "&" / "'" / "*" / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~" / DIGIT / ALPHA
int verifTchar(char* valeur, Noeud* pere, int index, int long_max);

//token = 1* tchar
int verifToken(char* valeur, Noeud* pere, int index, int long_max);

//transfer-coding = "chunked" / "compress" / "deflate" / "gzip" / transfer-extension
int verifTransfer_coding(char* valeur, Noeud* pere, int index, int long_max);

//Transfer-Encoding = * ( "," OWS ) transfer-coding * ( OWS "," [ OWS transfer-coding ] )
int verifTransfer_Encoding(char* valeur, Noeud* pere, int index, int long_max);

//Transfer-Encoding-header = "Transfer-Encoding" ":" OWS Transfer-Encoding OWS
int verifTransfer_Encoding_header(char* valeur, Noeud* pere, int index, int long_max);

//transfer-extension = token * ( OWS ";" OWS transfer-parameter )
int verifTransfer_extension(char* valeur, Noeud* pere, int index, int long_max);

//transfer-parameter = token BWS "=" BWS ( token / quoted-string )
int verifTransfer_parameter(char* valeur, Noeud* pere, int index, int long_max);

//type = token
int verifType(char* valeur, Noeud* pere, int index, int long_max);

//unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"
int verifUnreserved(char* valeur, Noeud* pere, int index, int long_max);

//uri-host = host
int verifUri_host(char* valeur, Noeud* pere, int index, int long_max);

//reg-name = * ( unreserved / pct-encoded / sub-delims )
int verifReg_name(char* valeur, Noeud* pere, int index, int long_max);

//VCHAR = %x21-7E
int verifVCHAR(char* valeur, Noeud* pere, int index, int long_max);

#endif
