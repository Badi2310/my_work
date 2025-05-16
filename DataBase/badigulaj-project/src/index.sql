create index federation_index on chess_project.players using HASH(federation_id);

--select name
--from chess_project.players p
--where p.federation = '0' #игроки Фиде

create index rating_index on chess_project.rating_history(rating);

--select * from chess_project.actual_rating (это представление в котором используется join по полю rating)

