int rowbin[rows];
		int count=0;
		for(int i=0; i <rows; i++)
			if(nim[i] > 0)
			rowbin[count++] =i;
			crow = rand() % count;
			sticks = 1+(rand() % nim[crow]);
			nim[crow]= nim[crow] - sticks;

			if( nim[crow] < 0)
			nim[crow] =0;