% traveling salesman
function Salesman()
close all
global gallNodes
global gallocs
global gmap
gallNodes = zeros(100,4);
gallocs = 1;
cities = rand(15,2); % col 1 is x and col 2 is y
numCities = size(cities,1);
gmap = zeros(numCities,1);

plot(cities(:,1), cities(:,2),'LineStyle','none','Marker','.','MarkerSize',16,'Color','r');hold on
tic
node = [0, 0, 0, 1]; % score, city, backPointer, memory
openList = zeros(100,4); % open list normal prioity queue, but I do not have one
openListLen = 0;
gallNodes(1,:) = node;
ind = 0;
city = 2;
score = 1;
while notDone(node, gallNodes, numCities)
    ind = ind + 1;
    children = getChildren(node, numCities, cities); 
    for i = 1:length(children)
        childNode = children(i,:); 
        if ~checkPath(node, childNode(city), gallNodes) % not in path
            openListLen = openListLen+1;
            if openListLen > size(openList,1)
                tmp = openList(ind:end,:);
                openList = zeros(size(openList,1)*2,4);
                openListLen = openListLen - ind; 
                openList(1:openListLen,:) = tmp;
                ind = 1;
            end
            openList(openListLen,:) = childNode; 
        end
    end
    [~, order] = sort(openList(ind:openListLen, score));
    openList(ind:openListLen,:) = openList(ind+order-1, :); 
    node = openList(ind,:);
    openListLen = openListLen-1;
    if openListLen-ind > 3000
        openListLen = 3000+ind;
    end
end
disp(toc)
plot(cities(gmap,1), cities(gmap,2),'Color','b');hold on
end

function children2 = getChildren(node, numCities, cities)
global gallNodes
global gallocs
score = 1;
city = 2;
backPointer = 3;
memory = 4;
children =  zeros(numCities,4);
for c = 1:numCities
    if (c == node(city) )
       continue; 
    end
    gallocs = gallocs+1;
    children(c,memory) = gallocs; 
    children(c, backPointer) = node(memory);
    children(c, city) = c;
    if (node(memory) ~= 1)
        children(c, score) = node(score)+ norm(cities(children(c, city),:)-cities(node(city),:));
    else
        children(c, score) = 0;
    end
    if (gallocs > size(gallNodes,1))
        tmp = gallNodes;
        gallNodes =  zeros(2*size(gallNodes,1),4);
        gallNodes(1:gallocs-1,:) = tmp;
    end
    gallNodes(gallocs,:) = children(c,:); % add node to memory
end
children2 = children([1:node(city)-1 node(city)+1:end],:);
end

function bool = notDone(node,gallNodes,numCities)
    backPointer = 3;
    memory = 4;
    city = 2;
    tmp = zeros(numCities,1);
    global gmap;
    ind = 1;
while (node(memory) ~= 1) 
    gmap(ind) = node(city);
    ind= ind+1;
    tmp(node(city)) = 1;
    node = gallNodes(node(backPointer),:);
end
bool = ~(sum(tmp)==numCities);
end

function bool = checkPath(node, checkCity, gallNodes)
    backPointer = 3;
    memory = 4;
    city = 2;
while (node(memory) ~= 1) 
    if (node(city) == checkCity)
        bool = 1;
        return
    end
    node = gallNodes(node(backPointer),:);
end
bool = 0;
end

