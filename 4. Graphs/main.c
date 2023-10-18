#include <stdio.h>
#include <stdbool.h>

#define max_city_amount 9
#define max_city_name_length 11

void printRoute(int previous_city[], int j, int price[], int start_city, char graph_names[max_city_amount][max_city_name_length]);
void dijkstra(int graph_adjacency_matrix[max_city_amount][max_city_amount], int start_city, int end_city, int number_of_cities, char graph_names[max_city_amount][max_city_name_length]);

int main()
{
    int number_of_cities = max_city_amount;
    ///*
    int graph_adjacency_matrix[max_city_amount][max_city_amount] =
    {
    { 0, 7, 0, 0, 0, 0, 0, 14, 0 },
    { 7, 0, 12, 0, 0, 0, 0, 10, 0 },
    { 0, 12, 0, 4, 0, 6, 0, 0, 2 },
    { 0, 0, 4, 0, 8, 3, 0, 0, 0 },
    { 0, 0, 0, 8, 0, 11, 0, 0, 0 },
    { 0, 0, 6, 3, 11, 0, 5, 0, 0 },
    { 0, 0, 0, 0, 0, 5, 0, 15, 4 },
    { 14, 10, 0, 0, 0, 0, 15, 0, 9 },
    { 0, 0, 2, 0, 0, 0, 4, 9, 0 }
    };
    //*/

//APACIOJ VILNIUS WASHINGTON NERA ROUTE
/*
int graph_adjacency_matrix[max_city_amount][max_city_amount] = {
    { 0, 7, 0, 0, 0, 0, 0, 14, 0 },
    { 7, 0, 12, 0, 0, 0, 0, 10, 0 },
    { 0, 12, 0, 4, 0, 6, 0, 0, 2 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 4, 0, 0, 3, 0, 0, 0 },
    { 0, 0, 6, 3, 0, 0, 5, 0, 0 },
    { 0, 0, 0, 0, 0, 5, 0, 15, 4 },
    { 14, 10, 0, 0, 0, 0, 15, 0, 9 },
    { 0, 0, 2, 0, 0, 0, 4, 9, 0 }
};
*/
    char graph_names[max_city_amount][max_city_name_length] =
    {
        "Beijing", "Nairobi", "Moscow", "Vilnius", "Washington", "Bali", "Paris", "Madrid", "Istanbul"
    };

    printf("List of cities you can travel from:\n");
    for (int i = 0; i < number_of_cities; i++)
    {
        printf("%d. %s\n", i, graph_names[i]);
    }

    //start city from the user
    int start_city;
    printf("Enter the number of the start city: ");
    scanf("%d", &start_city);

    //print the list of cities available to travel to
    printf("List of cities you can travel to:\n");
    for (int i = 0; i < number_of_cities; i++)
    {
        if (i != start_city)
        {
            printf("%d. %s\n", i, graph_names[i]);
        }
    }

    int end_city;
    printf("Enter the number of the end city: ");
    scanf("%d", &end_city);

    //finding the cheapest route
    dijkstra(graph_adjacency_matrix, start_city, end_city, number_of_cities, graph_names);

    return 0;
}

void printRoute(int previous_city[], int j, int price[], int start_city, char graph_names[max_city_amount][max_city_name_length])
{
    if (previous_city[j] == -1)
    {
        printf("%s ", graph_names[start_city]);
        return;
    }
    printRoute(previous_city, previous_city[j], price, start_city, graph_names);
    printf("-> ");
    printf("%s ", graph_names[j]);
}

void dijkstra(int graph_adjacency_matrix[max_city_amount][max_city_amount], int start_city, int end_city, int number_of_cities, char graph_names[max_city_amount][max_city_name_length])
{
    int INF = 999;
    int dist[max_city_amount];
    bool visited[max_city_amount];
    int previous_city[max_city_amount];
    int price[max_city_amount];

    for (int i = 0; i < number_of_cities; i++)
    {
        dist[i] = INF;
        previous_city[i] = -1;
        price[i] = 0;
        visited[i] = false;
    }

    dist[start_city] = 0;

    //finding the shortest path
    for (int count = 0; count < number_of_cities - 1; count++)
    {
        int current_city = -1;
        for (int i = 0; i < number_of_cities; i++)
        {
            if (!visited[i] && (current_city == -1 || dist[i] < dist[current_city]))
                {
                    current_city = i;
                }
        }

        visited[current_city] = true;

        for (int neighbor_city = 0; neighbor_city < number_of_cities; neighbor_city++)
        {
            if (!visited[neighbor_city] && graph_adjacency_matrix[current_city][neighbor_city] && dist[current_city] + graph_adjacency_matrix[current_city][neighbor_city] < dist[neighbor_city])
            {
                dist[neighbor_city] = dist[current_city] + graph_adjacency_matrix[current_city][neighbor_city];
                previous_city[neighbor_city] = current_city;
                price[neighbor_city] = price[current_city] + graph_adjacency_matrix[current_city][neighbor_city];
            }
        }
    }

    //checking if a route exists from the start city to the end city
    if (dist[end_city] == INF)
    {
        printf("No route exists from %s to %s.\n", graph_names[start_city], graph_names[end_city]);
    }
    else
    {
        printf("Cheapest route from %s to %s: ", graph_names[start_city], graph_names[end_city]);
        printRoute(previous_city, end_city, price, start_city, graph_names);
        printf("\nCheapest price: %d\n", price[end_city]);
    }
}
