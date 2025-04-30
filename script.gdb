define display_vars
  display data->map.matrix[row][col]
  display data->map.matrix[row][col+1]
  display data->map.matrix[row][col-1]
  display data->map.matrix[row+1][col]
  display data->map.matrix[row-1][col]
end

