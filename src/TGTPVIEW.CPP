void view_local_object (int body_logical_id)
{
	// Salva tutte le variabili modificate durante questa procedura.
	double _dzat_x = dzat_x, _dzat_y = dzat_y, _dzat_z = dzat_z;
	double _alfa = alfa, _beta = beta;

	// Inizializza le variabili di questa procedura.
	double d, k, xx, yy, zz;
	unsigned x, y, i, p, n;

	// Verifica se c'ä un bersaglio visibile.
	// Altrimenti oscura lo schermo e finiscila lç.
	if (body_logical_id == -1) {
		for (y = 0; y < 138; y++) {
			p = ((y + 10) << 8) + 16;
			i = riga[y + 100 - 138/2] + 160 - 200/2;
			for (x = 0; x < 200; x++) {
				n = 64 + (y >> 2) - (x >> 2);
				if (n > 127) n = 127;
				if (n < 64) n = 64;
				n_background[p] = n;
				p++;
				i++;
			}
		}
		return;
	}

	// Cancella pagina nascosta per visualizzazione temporanea.
	pclear (adapted, 0);

	// Calcola le coordinate per l'oggetto specificato.
	planet_xyz (body_logical_id);

	// Calcola la distanza dall'oggetto.
	xx = plx - dzat_x;
	yy = ply - dzat_y;
	zz = plz - dzat_z;
	d  = sqrt (xx*xx + yy*yy + zz*zz);

	// Porta la videocamera virtuale a breve distanza dall'oggetto.
	k       = (d - 1.5 * nearstar_p_ray[body_logical_id]) / d;
	dzat_x += xx * k;
	dzat_y += yy * k;
	dzat_z += zz * k;

	// Cerca il corretto angolo di approccio visuale.
	from_vehicle (); watch (dzat_x, dzat_y, dzat_z, plx, ply, plz);
	change_angle_of_view ();

	// Copia p_background a n_background (conserva mappa attuale).
	_fmemcpy (n_background, p_background, bk_bytes);

	// Elabora la mappa della superficie dell'oggetto.
	if (nearstar_p_owner[body_logical_id] > -1) {
		// mappatura luna.
		surface (body_logical_id,
			 nearstar_p_type[body_logical_id],
			 1000000			      *
			 nearstar_ray			      *
			 nearstar_p_type[body_logical_id]     *
			 nearstar_p_orb_orient[body_logical_id], 255);
	}
	else {
		// mappatura pianeta.
		surface (body_logical_id,
			 nearstar_p_type[body_logical_id],
			 1000000			      *
			 nearstar_p_type[body_logical_id]     *
			 nearstar_p_orb_seed[body_logical_id] *
			 nearstar_p_orb_tilt[body_logical_id] *
			 nearstar_p_orb_ecc[body_logical_id]  *
			 nearstar_p_orb_orient[body_logical_id], 255);
	}

	// Traccia l'oggetto sulla pagina nascosta,
	// usando i colori da 64 a 127.
	glass_bubble = 0;
	globe (359 - planet_viewpoint (_dzat_x, _dzat_z) + nearstar_p_rotation[body_logical_id],
	       adapted, p_background, n_globes_map, gl_bytes, plx, ply, plz, nearstar_p_ray[body_logical_id], 64);

	// Traduce l'immagine dell'oggetto in modo che possa essere
	// visualizzata come texture, usando il buffer "p_surfacemap".
	// La texture ä allineata a 256 righe in orizzontale, e viene
	// inquadrata nello schermo del target viewer dal punto (10;16)
	// per 200 pixels in orizzontale e 138 in verticale.
	for (y = 0; y < 138; y++) {
		p = ((y + 10) << 8) + 16;
		i = riga[y + 100 - 138/2] + 160 - 200/2;
		for (x = 0; x < 200; x++) {
			if (adapted[i])
				p_surfacemap[p] = adapted[i];
			else
				p_surfacemap[p] = 64 + (y >> 2);
			p++;
			i++;
		}
	}

	// Copia n_background a p_background (ripristina mappa precedente).
	_fmemcpy (p_background, n_background, bk_bytes);

	// Copia p_surfacemap a n_background per conservare l'immagine.
	_fmemcpy (n_background, p_surfacemap, ps_bytes);

	// Ripristina pagina nascosta.
	pcopy (adapted, adaptor);

	// Ripristina le variabili salvate.
	dzat_x = _dzat_x; dzat_y = _dzat_y; dzat_z = _dzat_z;
	alfa = _alfa; beta = _beta; change_angle_of_view ();
}
