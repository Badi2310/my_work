--актуальный рейтинг шахматистов
select first_name, rating
from chess_project.players p 
left join chess_project.rating_history rh 
on p.player_id = rh.player_id 
where rh.end_date = '9999-12-31 23:59:59.000'
order by rating desc;

--партии игроков, и кто в них победил
with player_game as (
		select * 
		from chess_project.players p
		right join chess_project.games g
		on p.player_id = g.white_player_id
	), player_game_player as (
		select *
		from player_game pg
		left join chess_project.players p
		on pg.black_player_id = p.player_id
	)
select white_player_id, black_player_id, winner
from player_game_player;

--игроки и их федерации
select first_name, last_name, federation_name
from chess_project.players p 
join chess_project.federations f
on p.federation_id = f.federation_id 

--федерации и их количество игроков
select f.federation_name, count(p.player_id) as player_count
from chess_project.federations f
left join chess_project.players p
on f.federation_id = p.federation_id
group by f.federation_name
having count(p.player_id) >= 2
order by player_count desc;

--победители (выйграли хотя бы одну партию)
select distinct p.first_name, p.last_name 
from chess_project.players p
left join chess_project.games g on p.player_id = g.winner
where g.winner is not null;

--игроки и их средний рейтинг
select p.first_name , round(avg(rh.rating)) as avg_rating
from chess_project.players p
left join chess_project.rating_history rh on p.player_id = rh.player_id
group by p.player_id, p.first_name
having avg(rh.rating) > 2200
order by avg_rating desc;

--игроки и количество партии
select p.player_id, p.first_name, p.last_name, count(g.game_id) as games_played
from chess_project.players p
left join chess_project.games g
on p.player_id in (g.white_player_id, g.black_player_id)
group by p.player_id
order by games_played desc
limit 5;

--ранк в федерации
with federation_player as (
		select p.player_id, federation_name, first_name, last_name
		from chess_project.federations f
		join chess_project.players p 
		on f.federation_id = p.federation_id 
	), player_rating as (
		select p.player_id, rating
		from chess_project.players p 
		left join chess_project.rating_history rh 
		on p.player_id = rh.player_id 
		where rh.end_date = '9999-12-31 23:59:59.000'
	)
select 	federation_name,
		first_name,
		last_name,
		rank() over (partition by federation_name order by rating)
from federation_player
join player_rating
on federation_player.player_id = player_rating.player_id 

--количество участников на одном турнире
SELECT 
    t.tournament_id, 
    COUNT(rt.player_id) AS total_players
FROM chess_project.tournaments t
JOIN chess_project.registration_on_tournament rt 
    ON t.tournament_id = rt.tournament_id
GROUP BY t.tournament_id
ORDER BY total_players DESC
LIMIT 5;

--количество турниров на которых поучавствовал игрок
SELECT 
    p.player_id, 
    p.first_name, 
    p.last_name, 
    COUNT(rt.tournament_id) AS total_tournaments
FROM chess_project.players p
JOIN chess_project.registration_on_tournament rt 
    ON p.player_id = rt.player_id
GROUP BY p.player_id
ORDER BY total_tournaments DESC
LIMIT 10;
