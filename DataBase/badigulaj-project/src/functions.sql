-- функция выводит список супер гроссмейтеров (рейтинг >= 2700)
create function chess_project.show_super_gm() returns table(player_id int, first_name text, last_name text, rating int) as $$
	select *
	from chess_project.actual_rating ar
	where ar.rating >= 2700;
$$ language sql;

select * from chess_project.show_super_gm();


-- функция для вывода всех изменений рейтинга игрока с определенного момента
create function chess_project.player_rating_history(player_id int, filter_date timestamp) returns table(rating int, start_date timestamp, end_date timestamp) as $$
	select rating, start_date, end_date
	from chess_project.rating_history rh
	where rh.player_id = player_id and start_date > filter_date;
$$ language sql;

select * from chess_project.player_rating_history(1, '2022-01-01');


--процедура по обновлению рейтинга игрока
create or replace procedure chess_project.update_rating(rating_id int, player_id int, last_rating int, start_date timestamp) as $$
	update chess_project.rating_history rh
	set end_date = start_date
	where rh.player_id = update_rating.player_id and end_date = '9999-12-31 23:59:59';

	insert into chess_project.rating_history(rating_id, player_id, rating, start_date, end_date) values
	(rating_id,
	 player_id,
	 last_rating,
	 start_date,
	 '9999-12-31 23:59:59');
$$ language sql;

call chess_project.update_rating(31, 10, 3000, '2024-03-01');