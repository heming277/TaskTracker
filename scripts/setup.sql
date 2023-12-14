-- setup.sql
-- Drop the table if it already exists.
DROP TABLE IF EXISTS tasks;

-- Create a new table for tasks.
CREATE TABLE tasks (
    task_id SERIAL PRIMARY KEY,
    description TEXT NOT NULL,
    status VARCHAR(50) NOT NULL
);
