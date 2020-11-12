% traveling salesman
function Salesman()
close all
global gallNodes
global gallocs
global gmap
global m
numCities = 15;
gallNodes = zeros(100,4+numCities,'uint32');
gallocs = 1;

maxNodes = 3000;
cities = [1 1].*rand(numCities,2); % col 1 is x and col 2 is y

m = zeros(numCities,'uint32');
for i = 1:numCities
    for j = 1:numCities
        m(i,j) = 10000*norm(cities(i,:)-cities(j,:)); 
    end
end

gmap = zeros(numCities,1,'uint32');

plot(cities(:,1), cities(:,2),'LineStyle','none','Marker','.','MarkerSize',16,'Color','r');hold on
tic
node = uint32([0, 0, 0, 1, zeros(1,numCities)]); % score, city, backPointer, mem
openList = zeros(100,4+numCities,'uint32'); % open list normal prioity queue, but I do not have one
openListLen = 0;
gallNodes(1,:) = node;
ind = 0;
city = 2;
score = 1;
mem = 4;
while notDone(node, gallNodes, numCities)
    ind = ind + 1;
    children = getChildren(node, numCities, m);
    for i = 1:size(children,1)
        childNode = children(i,:);
        if (node(mem+childNode(city))==0) %~checkPath(node, childNode(city)) % not in path
            openListLen = openListLen+1;
            if openListLen > size(openList,1)
                tmp = openList(ind:end,:);
                openList = zeros(size(openList,1)*2,4+numCities,'uint32');
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
    if openListLen-ind > maxNodes
        openListLen = maxNodes+ind;
    end
end
disp(['runtime for ' num2str(numCities) ' cities: ' num2str(toc)])
disp(['generated nodes: ' num2str(gallocs)])
plot(cities(gmap,1), cities(gmap,2),'Color','b');hold on
end
%% functions
function children = getChildren(node, numCities, m)
global gallNodes
global gallocs
% global m
score = 1;
city = 2;
backPointer = 3;
mem = 4;
children = repmat(node,numCities,1);
for c = 1:numCities
    if (c == node(city) )
        continue;
    end
    children(c,mem+node(city)) = 1;
    gallocs = gallocs+1;
    children(c,mem) = gallocs;
    children(c, backPointer) = node(mem);
    children(c, city) = c;
    if (node(mem) ~= 1)
        children(c, score) = node(score)+ m(children(c, city), node(city)); % 10000*norm(cities(children(c, city),:)-cities(node(city),:))
    else
        children(c, score) = 0;
    end
    if (gallocs > size(gallNodes,1))
        tmp = gallNodes;
        gallNodes =  zeros(2*size(gallNodes,1),4+numCities,'uint32');
        gallNodes(1:gallocs-1,:) = tmp;
    end
    gallNodes(gallocs,:) = children(c,:); % add node to mem
end
children = children([1:node(city)-1 node(city)+1:end],:);
end

function bool = notDone(node,allNodes,numCities)
backPointer = 3;
mem = 4;
city = 2;
tmp = zeros(numCities,1,'uint32');
global gmap
ind = 1;
while (node(mem) ~= 1)
    gmap(ind) = node(city);
    ind= ind+1;
    tmp(node(city)) = 1;
    node(1:4) = allNodes(node(backPointer),1:4); % partial copy
end
bool = ~(sum(tmp)==numCities);
end


