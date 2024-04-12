void
movestack(const Arg *arg) {
	Client *c = NULL, *p = NULL, *pc = NULL, *i;

	if(arg->i > 0) {
		/* find the client after selmon->sel */
		for(c = selmon->sel->next; c && (!ISVISIBLE(c) || c->isfloating); c = c->next);
		if(!c)
			for(c = selmon->clients; c && (!ISVISIBLE(c) || c->isfloating); c = c->next);

	}
	else {
		/* find the client before selmon->sel */
		for(i = selmon->clients; i != selmon->sel; i = i->next)
			if(ISVISIBLE(i) && !i->isfloating)
				c = i;
		if(!c)
			for(; i; i = i->next)
				if(ISVISIBLE(i) && !i->isfloating)
					c = i;
	}
	/* find the client before selmon->sel and c */
	for(i = selmon->clients; i && (!p || !pc); i = i->next) {
		if(i->next == selmon->sel)
			p = i;
		if(i->next == c)
			pc = i;
	}

	/* swap c and selmon->sel selmon->clients in the selmon->clients list */
	if(c && c != selmon->sel) {
		Client *temp = selmon->sel->next==c?selmon->sel:selmon->sel->next;
		selmon->sel->next = c->next==selmon->sel?c:c->next;
		c->next = temp;

		if(p && p != c)
			p->next = c;
		if(pc && pc != selmon->sel)
			pc->next = selmon->sel;

		if(selmon->sel == selmon->clients)
			selmon->clients = c;
		else if(c == selmon->clients)
			selmon->clients = selmon->sel;

		arrange(selmon);
	}
}

void
grid(Monitor *m) {
	unsigned int i, n, cx, cy, cw, ch, aw, ah, cols, rows;
	Client *c;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next))
		n++;

	/* grid dimensions */
	for(rows = 0; rows <= n/2; rows++)
		if(rows*rows >= n)
			break;
	cols = (rows && (rows - 1) * rows >= n) ? rows - 1 : rows;

	/* window geoms (cell height/width) */
	ch = m->wh / (rows ? rows : 1);
	cw = m->ww / (cols ? cols : 1);
	for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
		cx = m->wx + (i / rows) * cw;
		cy = m->wy + (i % rows) * ch;
		/* adjust height/width of last row/column's windows */
		ah = ((i + 1) % rows == 0) ? m->wh - ch * rows : 0;
		aw = (i >= rows * (cols - 1)) ? m->ww - cw * cols : 0;
		resize(c, cx, cy, cw - 2 * c->bw + aw, ch - 2 * c->bw + ah, False);
		i++;
	}
}

void
horizgrid(Monitor *m) {
	Client *c;
	unsigned int n, i;
	int w = 0;
	int ntop, nbottom = 0;

	/* Count windows */
	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);

	if(n == 0)
		return;
	else if(n == 1) { /* Just fill the whole screen */
		c = nexttiled(m->clients);
		resize(c, m->wx, m->wy, m->ww - (2*c->bw), m->wh - (2*c->bw), False);
	} else if(n == 2) { /* Split vertically */
		w = m->ww / 2;
		c = nexttiled(m->clients);
		resize(c, m->wx, m->wy, w - (2*c->bw), m->wh - (2*c->bw), False);
		c = nexttiled(c->next);
		resize(c, m->wx + w, m->wy, w - (2*c->bw), m->wh - (2*c->bw), False);
	} else {
		ntop = n / 2;
		nbottom = n - ntop;
		for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
			if(i < ntop)
				resize(c, m->wx + i * m->ww / ntop, m->wy, m->ww / ntop - (2*c->bw), m->wh / 2 - (2*c->bw), False);
			else
				resize(c, m->wx + (i - ntop) * m->ww / nbottom, m->wy + m->wh / 2, m->ww / nbottom - (2*c->bw), m->wh / 2 - (2*c->bw), False);
		}
	}
}
