//////
// DTXRAND.INL - Source file for DTXRandom
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////


inline DTX_PSZ DTXRandom::rndCreate( DTX_PSZ      pszData,
						             DTX_SMALLINT sSize )
{
	DTX_INT nValue;

	nValue = rand();

	memset(pszData,0,sSize);

    while (--sSize >= 0) 
		{
		*pszData++ = szItoa64[nValue&0x3f];
		nValue >>= 1;
		};

	return pszData;
}



