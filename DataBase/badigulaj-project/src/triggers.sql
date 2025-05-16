--Автоматическое закрытие предыдущего рейтинга перед вставкой нового
create or replace function chess_project.close_previous_rating()
returns trigger as $$
begin
    -- Закрываем текущую активную запись рейтинга
    update chess_project.rating_history
    set end_date = new.start_date
    where player_id = new.player_id
      and end_date = '9999-12-31';

    return new;
end;
$$ language plpgsql;

create trigger trg_close_previous_rating
before insert on chess_project.rating_history
for each row
execute function chess_project.close_previous_rating();


--Автоматическая регистрация игрока в турнире при добавлении игры
create or replace function chess_project.auto_register_players()
returns trigger as $$
begin
    -- Белый игрок
    insert into chess_project.registration_on_tournament(player_id, tournament_id)
    values (new.white_player_id, new.tournament_id)
    on conflict do nothing;

    -- Чёрный игрок
    insert into chess_project.registration_on_tournament(player_id, tournament_id)
    values (new.black_player_id, new.tournament_id)
    on conflict do nothing;

    return new;
end;
$$ language plpgsql;

create trigger trg_auto_register_players
before insert on chess_project.games
for each row
execute function chess_project.auto_register_players();


--Запрет удаления игрока, если он участвовал в играх
create or replace function chess_project.prevent_player_delete_if_played()
returns trigger as $$
begin
    if exists (
        select 1 from chess_project.games
        where white_player_id = old.player_id
           or black_player_id = old.player_id
    ) then
        raise exception 'Cannot delete player %, they have played games.', old.player_id;
    end if;

    return old;
end;
$$ language plpgsql;

create trigger trg_prevent_player_delete
before delete on chess_project.players
for each row
execute function chess_project.prevent_player_delete_if_played();
