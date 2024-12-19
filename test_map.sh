#!/bin/bash

# Couleurs
RED='\033[0;31m'      # Rouge pour les erreurs ou échecs
GREEN='\033[0;32m'    # Vert pour les succès
YELLOW='\033[1;33m'   # Jaune pour les avertissements
BLUE='\033[1;34m'     # Bleu pour le contexte (comme les noms de maps)
NC='\033[0m'          # Réinitialisation de la couleur (No Color)

# Chemin vers le dossier des maps
MAPS_DIR="./map"

# Liste des maps à tester
MAPS_NOT=(
  "color_invalid_rgb.cub"
  "color_missing.cub"
  "color_missing_ceiling_rgb.cub"
  "color_missing_floor_rgb.cub"
  "color_none.cub"
  "empty.cub"
  "filetype_missing"
  "filetype_wrong.buc"
  "forbidden.cub"
  "map_first.cub"
  "map_middle.cub"
  "map_missing.cub"
  "map_only.cub"
  "map_too_small.cub"
  "player_multiple.cub"
  "player_none.cub"
  "player_on_edge.cub"
  "textures_dir.cub"
  "textures_duplicates.cub"
  "textures_invalid.cub"
  "textures_missing.cub"
  "textures_none.cub"
  "textures_not_xpm.cub"
  "wall_hole_east.cub"
  "wall_hole_north.cub"
  "wall_hole_south.cub"
  "wall_hole_west.cub"
  "wall_none.cub"
  "map_wrongext.cb"
  "map_false.cub"
)

MAPS=(
  "map_official.cub"
  "map_big.cub"
)

# Test chaque map
for map in "${MAPS_NOT[@]}"; do
  echo -e "${YELLOW}\nShould not be ok : Testing ${NC}$map:"

  # Vérifie si le fichier existe
  if [ -f "$MAPS_DIR/$map" ]; then
    # Exécute le programme avec la map et capture le résultat
    OUTPUT=$(./cub3D "$MAPS_DIR/$map" 2>&1)
    echo -e "${BLUE}$OUTPUT${NC}"
  else
    echo -e "${BLUE}Map file '$map' not found in $MAPS_DIR.${NC}"
  fi
done

for map in "${MAPS[@]}"; do
  echo -e "${GREEN}\nShould be ok : Testing ${NC}$map:"

  # Vérifie si le fichier existe
  if [ -f "$MAPS_DIR/$map" ]; then
    # Exécute le programme avec la map et capture le résultat
    OUTPUT=$(./cub3D "$MAPS_DIR/$map" 2>&1)
    echo -e "${GREEN}$OUTPUT${NC}"
  else
    echo -e "${BLUE}Map file '$map' not found in $MAPS_DIR.${NC}"
  fi
done
