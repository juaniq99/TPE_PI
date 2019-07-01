int diaSemana (int dia, int mes, int anio)
{
	if ( mes==1 || mes==2 )
			--anio;
	int c=anio/100;							// Primeros 2 dígitos año
	int g=anio-c*100;						// Últimos 2 dígitos año
	int e[]={0,3,2,5,0,3,5,1,4,6,2,4};		// Constante del mes
	int f;									// Constante del siglo
	switch (c%4)
	{
		case 0: f=0; break;
		case 1: f=5; break;
		case 2: f=3; break;
		case 3: f=1; break;
	}
	return (dia+e[mes-1]+f+g+g/4)%7;
}