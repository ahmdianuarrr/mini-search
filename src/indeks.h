#pragma once
#include <map>
#include <string>
#include <utility>
#include <vector>

using Indeks = std::map<std::string, std::map<int, int>>;

Indeks bangunIndeks(const std::vector<std::string>& dokumen);

std::vector<std::pair<int, int>> cari(const Indeks& indeks, const std::string& kueri);