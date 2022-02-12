#include <stdint.h>

/* *
 * Lookup table to translate the most common accents
 * */
static char TRANSLIT[] = {
    /* À 192 =  */'A',
    /* Á 193 =  */'A',
    /* Â 194 =  */'A',
    /* Ã 195 =  */'A',
    /* Ä 196 =  */'A',
    /* Å 197 =  */'A',
    /* Æ 198 =  */0,
    /* Ç 199 =  */'C',
    /* È 200 =  */'E',
    /* É 201 =  */'E',
    /* Ê 202 =  */'E',
    /* Ë 203 =  */'E',
    /* Ì 204 =  */'I',
    /* Í 205 =  */'I',
    /* Î 206 =  */'I',
    /* Ï 207 =  */'I',
    /* Ð 208 =  */'D',
    /* Ñ 209 =  */'N',
    /* Ò 210 =  */'O',
    /* Ó 211 =  */'O',
    /* Ô 212 =  */'O',
    /* Õ 213 =  */'O',
    /* Ö 214 =  */'O',
    /* × 215 =  */'x',
    /* Ø 216 =  */'O',
    /* Ù 217 =  */'U',
    /* Ú 218 =  */'U',
    /* Û 219 =  */'U',
    /* Ü 220 =  */'U',
    /* Ý 221 =  */'Y',
    /* Þ 222 =  */0,
    /* ß 223 =  */'s',
    /* à 224 =  */'a',
    /* á 225 =  */'a',
    /* â 226 =  */'a',
    /* ã 227 =  */'a',
    /* ä 228 =  */'a',
    /* å 229 =  */'a',
    /* æ 230 =  */0,
    /* ç 231 =  */'c',
    /* è 232 =  */'e',
    /* é 233 =  */'e',
    /* ê 234 =  */'e',
    /* ë 235 =  */'e',
    /* ì 236 =  */'i',
    /* í 237 =  */'i',
    /* î 238 =  */'i',
    /* ï 239 =  */'i',
    /* ð 240 =  */0,
    /* ñ 241 =  */'n',
    /* ò 242 =  */'o',
    /* ó 243 =  */'o',
    /* ô 244 =  */'o',
    /* õ 245 =  */'o',
    /* ö 246 =  */'o',
    /* ÷ 247 =  */0,
    /* ø 248 =  */'o',
    /* ù 249 =  */'u',
    /* ú 250 =  */'u',
    /* û 251 =  */'u',
    /* ü 252 =  */'u',
    /* ý 253 =  */'y',
    /* þ 254 =  */0,
    /* ÿ 255 =  */'y',
    /* Ā 256 =  */'A',
    /* ā 257 =  */'a',
    /* Ă 258 =  */'A',
    /* ă 259 =  */'a',
    /* Ą 260 =  */'A',
    /* ą 261 =  */'a',
    /* Ć 262 =  */'C',
    /* ć 263 =  */'c',
    /* Ĉ 264 =  */'C',
    /* ĉ 265 =  */'c',
    /* Ċ 266 =  */'C',
    /* ċ 267 =  */'c',
    /* Č 268 =  */'C',
    /* č 269 =  */'c',
    /* Ď 270 =  */'D',
    /* ď 271 =  */'d',
    /* Đ 272 =  */'D',
    /* đ 273 =  */'d',
    /* Ē 274 =  */'E',
    /* ē 275 =  */'e',
    /* Ĕ 276 =  */'E',
    /* ĕ 277 =  */'e',
    /* Ė 278 =  */'E',
    /* ė 279 =  */'e',
    /* Ę 280 =  */'E',
    /* ę 281 =  */'e',
    /* Ě 282 =  */'E',
    /* ě 283 =  */'e',
    /* Ĝ 284 =  */'G',
    /* ĝ 285 =  */'g',
    /* Ğ 286 =  */'G',
    /* ğ 287 =  */'g',
    /* Ġ 288 =  */'G',
    /* ġ 289 =  */'g',
    /* Ģ 290 =  */'G',
    /* ģ 291 =  */'g',
    /* Ĥ 292 =  */'H',
    /* ĥ 293 =  */'h',
    /* Ħ 294 =  */'H',
    /* ħ 295 =  */'h',
    /* Ĩ 296 =  */'I',
    /* ĩ 297 =  */'i',
    /* Ī 298 =  */'I',
    /* ī 299 =  */'i',
    /* Ĭ 300 =  */'I',
    /* ĭ 301 =  */'i',
    /* Į 302 =  */'I',
    /* į 303 =  */'i',
    /* İ 304 =  */'I',
    /* ı 305 =  */'i',
    /* Ĳ 306 =  */0,
    /* ĳ 307 =  */0,
    /* Ĵ 308 =  */'J',
    /* ĵ 309 =  */'j',
    /* Ķ 310 =  */'K',
    /* ķ 311 =  */'k',
    /* ĸ 312 =  */'k',
    /* Ĺ 313 =  */'L',
    /* ĺ 314 =  */'l',
    /* Ļ 315 =  */'L',
    /* ļ 316 =  */'l',
    /* Ľ 317 =  */'L',
    /* ľ 318 =  */'l',
    /* Ŀ 319 =  */'L',
    /* ŀ 320 =  */'l',
    /* Ł 321 =  */'L',
    /* ł 322 =  */'l',
    /* Ń 323 =  */'N',
    /* ń 324 =  */'n',
    /* Ņ 325 =  */'N',
    /* ņ 326 =  */'n',
    /* Ň 327 =  */'N',
    /* ň 328 =  */'n',
    /* ŉ 329 =  */'N',
    /* Ŋ 330 =  */'n',
    /* ŋ 331 =  */'N',
    /* Ō 332 =  */'O',
    /* ō 333 =  */'o',
    /* Ŏ 334 =  */'O',
    /* ŏ 335 =  */'o',
    /* Ő 336 =  */'O',
    /* ő 337 =  */'o',
    /* Œ 338 =  */0,
    /* œ 339 =  */0,
    /* Ŕ 340 =  */'R',
    /* ŕ 341 =  */'r',
    /* Ŗ 342 =  */'R',
    /* ŗ 343 =  */'r',
    /* Ř 344 =  */'R',
    /* ř 345 =  */'r',
    /* Ś 346 =  */'S',
    /* ś 347 =  */'s',
    /* Ŝ 348 =  */'S',
    /* ŝ 349 =  */'s',
    /* Ş 350 =  */'S',
    /* ş 351 =  */'s',
    /* Š 352 =  */'S',
    /* š 353 =  */'s',
    /* Ţ 354 =  */'T',
    /* ţ 355 =  */'t',
    /* Ť 356 =  */'T',
    /* ť 357 =  */'t',
    /* Ŧ 358 =  */'T',
    /* ŧ 359 =  */'t',
    /* Ũ 360 =  */'U',
    /* ũ 361 =  */'u',
    /* Ū 362 =  */'U',
    /* ū 363 =  */'u',
    /* Ŭ 364 =  */'U',
    /* ŭ 365 =  */'u',
    /* Ů 366 =  */'U',
    /* ů 367 =  */'u',
    /* Ű 368 =  */'U',
    /* ű 369 =  */'u',
    /* Ų 370 =  */'U',
    /* ų 371 =  */'u',
    /* Ŵ 372 =  */'W',
    /* ŵ 373 =  */'w',
    /* Ŷ 374 =  */'Y',
    /* ŷ 375 =  */'y',
    /* Ÿ 376 =  */'Y',
    /* Ź 377 =  */'Z',
    /* ź 378 =  */'z',
    /* Ż 379 =  */'Z',
    /* ż 380 =  */'z',
    /* Ž 381 =  */'Z',
    /* ž 382 =  */'z',
    /* ſ 383 =  */'s'
};

/* Remove the most common accents using a lookup table*/
uint32_t remove_accent(uint32_t c){
    if(c < 192  || c > 383) return c;
    // assert((c - 192) >= 0 && (c - 192 < 192));
    uint32_t res = (uint32_t)TRANSLIT[c - 192];
    if(res == 0) return c;
    return res;
}