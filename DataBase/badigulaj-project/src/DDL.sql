create table if not exists chess_project.federations (
    federation_id integer primary key,
    federation_name varchar(200)
);

create table if not exists chess_project.players (
    player_id integer primary key,
    first_name varchar(200),
    last_name varchar(200),
    federation_id integer,
    foreign key (federation_id) references chess_project.federations(federation_id)
);

create table if not exists chess_project.tournaments(
	tournament_id integer primary key,
	federation_id integer,
	status integer,
	foreign key (federation_id) references chess_project.federations(federation_id)
);

create table if not exists chess_project.registration_on_tournament (
    player_id integer,
    tournament_id integer,
    primary key (player_id, tournament_id),
    foreign key (player_id) references chess_project.players(player_id) on delete cascade,
    foreign key (tournament_id) references chess_project.tournaments(tournament_id) on delete cascade
);

create table if not exists chess_project.games(
	game_id integer primary key,
	white_player_id integer,
	black_player_id integer,
	tournament_id integer,
	winner integer,
	
	foreign key (white_player_id) references chess_project.players(player_id),
	foreign key (black_player_id) references chess_project.players(player_id),
	foreign key (tournament_id) references chess_project.tournaments(tournament_id)
);

create table if not exists chess_project.rating_history(
	rating_id integer primary key,
	player_id integer,
	rating integer,
	start_date timestamp,
	end_date timestamp DEFAULT '9999-12-31',
	
	foreign key(player_id) references chess_project.players(player_id)
);

