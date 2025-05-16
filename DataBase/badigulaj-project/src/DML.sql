insert into chess_project.federations values
	(1, 'FIDE'),
	(2, 'United States Chess Federation'),
	(3, 'Russian Chess Federation'),
	(4, 'China Chess Association'),
	(5, 'Indian Chess Federation'),
	(6, 'European Chess Union'),
	(7, 'French Chess Federation'),
	(8, 'German Chess Federation'),
	(9, 'Spanish Chess Federation'),
	(10, 'Brazilian Chess Federation'),
	(11, 'Canadian Chess Federation'),
	(12, 'British Chess Federation'),
	(13, 'Italian Chess Federation'),
	(14, 'Norwegian Chess Federation'),
	(15, 'Argentinian Chess Federation'),
	(16, 'Azerbaijan Chess Federation');

insert into chess_project.players values
	(1, 'Magnus', 'Carlsen', 14),  -- Норвегия
	(2, 'Ian', 'Nepomniachtchi', 3),  -- Россия
	(3, 'Ding', 'Liren', 4),  -- Китай
	(4, 'Fabiano', 'Caruana', 2),  -- США
	(5, 'Hikaru', 'Nakamura', 2),  -- США
	(6, 'Viswanathan', 'Anand', 5),  -- Индия
	(7, 'Alireza', 'Firouzja', 7),  -- Франция
	(8, 'Levon', 'Aronian', 2),  -- США (перешел из Армении)
	(9, 'Anish', 'Giri', 6),  -- Европа (Нидерланды)
	(10, 'Richard', 'Rapport', 6),  -- Европа (Венгрия)
	(11, 'Wesley', 'So', 2),  -- США (родом с Филиппин)
	(12, 'Maxime', 'Vachier-Lagrave', 7),  -- Франция
	(13, 'Shakhriyar', 'Mamedyarov', 16),  -- Азербайджан
	(14, 'Teimour', 'Radjabov', 16),  -- Азербайджан
	(15, 'Dommaraju', 'Gukesh', 5);  -- Индия

insert into chess_project.tournaments (tournament_id, federation_id, status) values
	(1, 1, 1),  -- FIDE World Chess Championship (Чемпионат мира)
	(2, 1, 2),  -- Candidates Tournament (Турнир претендентов)
	(3, 1, 3),  -- Grand Chess Tour (Элитный турнир)
	(4, 4, 4),  -- China Chess Championship (Национальный чемпионат)
	(5, 5, 3),  -- Tata Steel Chess India (Элитный турнир)
	(6, 7, 4),  -- French Chess Championship (Национальный чемпионат)
	(7, 10, 5), -- Brazil Open Chess Tournament (Открытый турнир)
	(8, 12, 4), -- British Chess Championship (Национальный чемпионат)
	(9, 14, 3), -- Norway Chess (Элитный турнир)
	(10, 16, 4), -- Azerbaijan Chess Championship (Национальный чемпионат)
	(11, 6, 3),  -- European Individual Chess Championship (Элитный турнир)
	(12, 8, 4),  -- German Chess Masters (Национальный чемпионат)
	(13, 9, 5),  -- Spanish Chess Open (Открытый турнир)
	(14, 11, 4), -- Canadian Chess Championship (Национальный чемпионат)
	(15, 13, 5); -- Italian Chess Cup (Открытый турнир)
	
insert into chess_project.registration_on_tournament values
	(1, 1),  -- Magnus Carlsen на Чемпионате мира
	(2, 1),  -- Ian Nepomniachtchi на Чемпионате мира
	(3, 2),  -- Ding Liren в Турнире претендентов
	(4, 2),  -- Fabiano Caruana в Турнире претендентов
	(5, 2),  -- Hikaru Nakamura в Турнире претендентов
	(6, 3),  -- Viswanathan Anand в элитном турнире
	(7, 3),  -- Alireza Firouzja в элитном турнире
	(8, 4),  -- Levon Aronian в элитном турнире
	(9, 4),  -- Anish Giri в элитном турнире
	(10, 5), -- Richard Rapport в элитном турнире
	(11, 5), -- Wesley So в элитном турнире
	(12, 6), -- Shakhriyar Mamedyarov в элитном турнире
	(13, 6), -- Teimour Radjabov в элитном турнире
	(1, 7),  -- Magnus Carlsen на крупном турнире
	(2, 7),  -- Ian Nepomniachtchi на крупном турнире
	(3, 8),  -- Ding Liren на крупном турнире
	(4, 8),  -- Fabiano Caruana на крупном турнире
	(5, 9),  -- Hikaru Nakamura на крупном турнире
	(6, 9),  -- Viswanathan Anand на крупном турнире
	(7, 10), -- Alireza Firouzja на крупном турнире
	(8, 10), -- Levon Aronian на крупном турнире
	(9, 11), -- Anish Giri на крупном турнире
	(10, 11),-- Richard Rapport на крупном турнире
	(11, 12),-- Wesley So на крупном турнире
	(12, 12),-- Shakhriyar Mamedyarov на крупном турнире
	(13, 13),-- Teimour Radjabov на крупном турнире
	(1, 14), -- Magnus Carlsen в клубном турнире
	(2, 14), -- Ian Nepomniachtchi в клубном турнире
	(3, 15), -- Ding Liren в клубном турнире
	(4, 15); -- Fabiano Caruana в клубном турнире

insert into chess_project.games values
	(1, 1, 2, 1, 1),  -- Magnus Carlsen победил Ian Nepomniachtchi
	(2, 2, 1, 1, 2),  -- Ian Nepomniachtchi победил Magnus Carlsen
	(3, 1, 2, 1, 0),  -- Ничья между Magnus Carlsen и Ian Nepomniachtchi
	(4, 3, 4, 2, 3),  -- Ding Liren победил Fabiano Caruana
	(5, 4, 5, 2, 4),  -- Fabiano Caruana победил Hikaru Nakamura
	(6, 5, 3, 2, 0),  -- Ничья между Hikaru Nakamura и Ding Liren
	(7, 6, 7, 3, 7),  -- Alireza Firouzja победил Viswanathan Anand
	(8, 7, 8, 3, 7),  -- Alireza Firouzja победил Levon Aronian
	(9, 8, 6, 3, 8),  -- Levon Aronian победил Viswanathan Anand
	(10, 9, 10, 4, 9), -- Anish Giri победил Richard Rapport
	(11, 10, 11, 4, 0),-- Ничья между Richard Rapport и Wesley So
	(12, 11, 9, 4, 11),-- Wesley So победил Anish Giri
	(13, 12, 13, 5, 12),-- Shakhriyar Mamedyarov победил Teimour Radjabov
	(14, 13, 1, 5, 0), -- Ничья между Teimour Radjabov и Magnus Carlsen
	(15, 1, 12, 5, 1), -- Magnus Carlsen победил Shakhriyar Mamedyarov
	(16, 2, 3, 6, 2),  -- Ian Nepomniachtchi победил Ding Liren
	(17, 4, 5, 6, 5),  -- Hikaru Nakamura победил Fabiano Caruana
	(18, 6, 7, 6, 0),  -- Ничья между Viswanathan Anand и Alireza Firouzja
	(19, 8, 9, 7, 8),  -- Levon Aronian победил Anish Giri
	(20, 10, 11, 7, 0),-- Ничья между Richard Rapport и Wesley So
	(21, 12, 13, 7, 12),-- Shakhriyar Mamedyarov победил Teimour Radjabov
	(22, 1, 3, 8, 0), -- Ничья между Magnus Carlsen и Ding Liren
	(23, 2, 4, 8, 2),  -- Ian Nepomniachtchi победил Fabiano Caruana
	(24, 5, 6, 8, 6),  -- Viswanathan Anand победил Hikaru Nakamura
	(25, 7, 8, 9, 7),  -- Alireza Firouzja победил Levon Aronian
	(26, 9, 10, 9, 0),-- Ничья между Anish Giri и Richard Rapport
	(27, 11, 12, 9, 11),-- Wesley So победил Shakhriyar Mamedyarov
	(28, 13, 1, 10, 0), -- Ничья между Teimour Radjabov и Magnus Carlsen
	(29, 2, 3, 10, 3),  -- Ding Liren победил Ian Nepomniachtchi
	(30, 4, 5, 10, 4);  -- Fabiano Caruana победил Hikaru Nakamura

insert into chess_project.rating_history values
	(1, 1, 2850, '2023-01-01 00:00:00', '2023-06-30 23:59:59'),  -- Magnus Carlsen
	(2, 1, 2845, '2023-07-01 00:00:00', '2023-12-31 23:59:59'),  -- Magnus Carlsen
	(3, 1, 2840, '2024-01-01 00:00:00', '9999-12-31 23:59:59'),  -- Magnus Carlsen (актуальный рейтинг)
	(4, 2, 2795, '2023-01-01 00:00:00', '2023-06-30 23:59:59'),  -- Ian Nepomniachtchi
	(5, 2, 2790, '2023-07-01 00:00:00', '2023-12-31 23:59:59'),  -- Ian Nepomniachtchi
	(6, 2, 2785, '2024-01-01 00:00:00', '9999-12-31 23:59:59'),  -- Ian Nepomniachtchi (актуальный рейтинг)
	(7, 3, 2780, '2023-01-01 00:00:00', '2023-06-30 23:59:59'),  -- Ding Liren
	(8, 3, 2778, '2023-07-01 00:00:00', '2023-12-31 23:59:59'),  -- Ding Liren
	(9, 3, 2775, '2024-01-01 00:00:00', '9999-12-31 23:59:59'),  -- Ding Liren (актуальный рейтинг)
	(10, 4, 2770, '2023-01-01 00:00:00', '2023-06-30 23:59:59'),  -- Fabiano Caruana
	(11, 4, 2765, '2023-07-01 00:00:00', '2023-12-31 23:59:59'),  -- Fabiano Caruana
	(12, 4, 2760, '2024-01-01 00:00:00', '9999-12-31 23:59:59'),  -- Fabiano Caruana (актуальный рейтинг)
	(13, 5, 2760, '2023-01-01 00:00:00', '2023-06-30 23:59:59'),  -- Hikaru Nakamura
	(14, 5, 2755, '2023-07-01 00:00:00', '2023-12-31 23:59:59'),  -- Hikaru Nakamura
	(15, 5, 2750, '2024-01-01 00:00:00', '9999-12-31 23:59:59'),  -- Hikaru Nakamura (актуальный рейтинг)
	(16, 6, 2750, '2023-01-01 00:00:00', '2023-06-30 23:59:59'),  -- Viswanathan Anand
	(17, 6, 2745, '2023-07-01 00:00:00', '2023-12-31 23:59:59'),  -- Viswanathan Anand
	(18, 6, 2740, '2024-01-01 00:00:00', '9999-12-31 23:59:59'),  -- Viswanathan Anand (актуальный рейтинг)
	(19, 7, 2740, '2023-01-01 00:00:00', '2023-06-30 23:59:59'),  -- Alireza Firouzja
	(20, 7, 2735, '2023-07-01 00:00:00', '2023-12-31 23:59:59'),  -- Alireza Firouzja
	(21, 7, 2730, '2024-01-01 00:00:00', '9999-12-31 23:59:59'),  -- Alireza Firouzja (актуальный рейтинг)
	(22, 8, 2735, '2023-01-01 00:00:00', '2023-06-30 23:59:59'),  -- Levon Aronian
	(23, 8, 2730, '2023-07-01 00:00:00', '2023-12-31 23:59:59'),  -- Levon Aronian
	(24, 8, 2725, '2024-01-01 00:00:00', '9999-12-31 23:59:59'),  -- Levon Aronian (актуальный рейтинг)
	(25, 9, 2720, '2023-01-01 00:00:00', '2023-06-30 23:59:59'),  -- Anish Giri
	(26, 9, 2715, '2023-07-01 00:00:00', '2023-12-31 23:59:59'),  -- Anish Giri
	(27, 9, 2710, '2024-01-01 00:00:00', '9999-12-31 23:59:59'),  -- Anish Giri (актуальный рейтинг)
	(28, 10, 2705, '2023-01-01 00:00:00', '2023-06-30 23:59:59'),  -- Richard Rapport
	(29, 10, 2700, '2023-07-01 00:00:00', '2023-12-31 23:59:59'),  -- Richard Rapport
	(30, 10, 2695, '2024-01-01 00:00:00', '9999-12-31 23:59:59');  -- Richard Rapport (актуальный рейтинг)
