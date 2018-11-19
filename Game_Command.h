#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

void do_new_command(Model& model, char type, int id, int x, int y);
void do_move_command(Model& model, int id, int x, int y);
void do_work_a_depot_command(Model& model, int personId, int depotId);
void do_deposit_moon_stones_command(Model& model, int personId, int stationId);
void do_stop_command(Model& model, int personId);
void do_lock_in_at_station_command(Model& model, int personId, int stationId);
void do_attack_command(Model& model, int alienId, int personId);
void do_go_command(Model& model);
void do_run_command(Model& model);
void do_quit_command(Model& model);

#endif