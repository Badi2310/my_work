--актуальный рейтинг игроков

create view chess_project.actual_rating as
select p.player_id, p.first_name, p.last_name, rh.rating
from chess_project.players p 
left join chess_project.rating_history rh 
on p.player_id = rh.player_id 
where rh.end_date = '9999-12-31 23:59:59.000'
order by rating desc;

--игроки и их федерации
create view chess_project.player_federation as
select p.player_id, p.first_name, p.last_name, f.federation_name
from chess_project.players p 
join chess_project.federations f
on p.federation_id = f.federation_id;
